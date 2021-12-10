#include "Control_DB.h"
#include "sensor.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>
#include <sstream>
#include <ctime>
#include <unistd.h>

using namespace std;

int main (int argc , char** argv){
    int Dia_calor = 0;
    int Dias[2];
    Dias [0] = 0, Dias [1] = 0;
    int contador = 0;
    int Mal_dia = 0;
    int Datos_dia = 1440;
    string us, con, uss;
    double Datos[18];
    int D_Us[7];

    for (int i = 0 ; i < 18 ; i++){
        Datos[i] = 0;
    }
    for (int i = 0 ; i < 7 ; i++){
        D_Us[i] = 0;
    }

    Temperatura T;
    Humedad H;
    Velocidad V;
    DViento D;
    Precipitacion P;
    Intensidad I;
    Control_DB control("Sensores.db");
    int inicio = 0;

    if (argc==3){
        us=argv[1];
        con=argv[2];
    }else {
        cout << "Debe ingresar su usuario y contraseña" << endl;
        return 1;
    }

    control.abrir_DB();
    control.Comprobar_U(us, con, D_Us);
    control.cerrar_DB();

    if (D_Us[0] >= 1 && D_Us[0] <= 20) {
        inicio = 1;
        uss = us;
    }
    else {
        cout << "Usuario o contraseña incorrectos, por favor intente nuevamente" << endl;
        return 1;
    }

    /*
    while (inicio == 0){
        cout << "Ingrese su usuario: ";
        cin >> us;
        cout << "Ingrese su contraseña: ";
        cin >> con;
        control.abrir_DB();
        control.Comprobar_U(us, con, D_Us);
        control.cerrar_DB();
        if (D_Us[0] >= 1 && D_Us[0] <= 20) {
            inicio = 1;
            uss = us;
        }
        else cout << "Usuario o contraseña incorrectos, por favor intente nuevamente" << endl;
    }
    */
    control.abrir_DB();
    control.guardarInicio_DB(uss);
    control.cerrar_DB();

    time_t currentTime;
    struct tm *localTime;
    time( &currentTime );
    localTime = localtime( &currentTime );
    int Hor_act   = localTime->tm_hour;
    int Min_act    = localTime->tm_min;
    int Dato_ref = (Hor_act*60)+Min_act;
    int Datos_res = Datos_dia - Dato_ref;
    cout << "Quedan " << Datos_res << " datos por tomar el día de hoy" << endl;
    int Hora_dato = Dato_ref;

    while (inicio == 1){
        while(contador < 60){
            T.actualizar(contador, D_Us[0]);
            H.actualizar(contador, D_Us[1]);
            V.actualizar(contador, D_Us[2]);
            D.actualizar(contador, D_Us[3]);
            P.actualizar(contador, D_Us[4]);
            I.actualizar(contador, D_Us[5]);
            contador++;
            usleep(50);
        }
        Datos[0] = T.prom(), Datos[1] = T.maximo(), Datos[2] = T.minimo();
        Datos[3] = H.prom(), Datos[4] = H.maximo(), Datos[5] = H.minimo();
        Datos[6] = V.prom(), Datos[7] = V.maximo(), Datos[8] = V.minimo();
        Datos[9] = D.prom(), Datos[10] = D.maximo(), Datos[11] = D.minimo();
        Datos[12] = P.prom(), Datos[13] = P.maximo(), Datos[14] = P.minimo();
        Datos[15] = I.prom(), Datos[16] = I.maximo(), Datos[17] = I.minimo();
        if (Datos[0] < 10 && Datos[3] > 80) Mal_dia = 1;
        control.abrir_DB();
        if (Hora_dato % Datos_dia == 0){
            Dia_calor = control.Promedio_T(Datos_res);
            control.GuardarDia_DB(Mal_dia, Dia_calor, Dato_ref);
            control.ObtenerDias_DB(Dias);
            if (D_Us[6] == 1){
                if (Dias[0] == 0) cout << "Día de condición normal para la papa" << endl;
                else if (Dias[0] == 1) cout << "Advertencia: Primer día con malas condiciones en el cultivo de papa, se recomienda precacución" << endl;
                else cout << "PELIGRO: EL CULTIVO DE PAPA LLEVA " << Dias[0] << " DÍAS EN CONDICIONES NO FAVORABLES, SE SOLICITA CUIDADO" << endl;
            }
            else{
                if (Dias[1] == 0) cout << "Advertencia: Condiciones requeridas no cumplidas, el conteo de días para la cosecha se ha reiniciado." << endl;
                else if (Dias[1] >= 1 && Dias[1] < 90) cout << "Día de calor, faltan " << 90 - Dias[1] << " días para cosecha." << endl;
                else cout << "90 días de calor completados, se puede cosechar el cultivo" << endl;
            }
            Mal_dia = 0;
            Hora_dato = 1;
            Datos_res = Datos_dia;
            Dato_ref = Datos_dia;
        }
        Hora_dato++;
        control.guardarDatos_DB(Datos);
        control.cerrar_DB();
        T.reiniciar(), H.reiniciar(), V.reiniciar(), D.reiniciar(), P.reiniciar(), I.reiniciar();
        contador = 0;
    }
}
