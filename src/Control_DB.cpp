#include "Control_DB.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <stdlib.h>


using namespace std;

Control_DB::Control_DB(string path){
    _url = path;
}

bool Control_DB::abrir_DB(){
    int rc;
    rc = sqlite3_open( _url.c_str(), &_db );

    // Qué pasaría si el archivo se corrompe? Cómo podemos mitigar ese riesgo?
    /* CREATE TABLE IF NOT EXISTS `TBL_DATOS` ( `id_muestra` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
     * `fecha` TEXT NOT NULL, `hora` TEXT NOT NULL, `latitud` REAL NOT NULL, `longitud` REAL NOT NULL,
     * `altura` REAL NOT NULL, `temperatura` REAL NOT NULL, `humedad` REAL NOT NULL, `velocidad_viento`
     * REAL NOT NULL, `direccion_viento` REAL NOT NULL, `precipitacion` REAL NOT NULL )
     * */

    if( rc ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
       return(0);
    }
    return true;}

bool Control_DB::crear_DB()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sqlstr;

    /* Open database */
    rc = sqlite3_open("Sensores.db", &db);

    if( rc != 0 ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return(1);
    } else {
       fprintf(stdout, "Opened database successfully\n");
    }

       /* Create SQL statement */
    sqlstr="CREATE TABLE IF NOT EXISTS Usuarios (" \
           "Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
           "Usuario TEXT NOT NULL UNIQUE," \
           "Contraseña TEXT NOT NULL," \
           "Nombre TEXT NOT NULL," \
           "Apellido	TEXT NOT NULL," \
           "Documento INTEGER NOT NULL UNIQUE," \
           "Fecha_nac TEXT NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return (2);
    } else {
       fprintf(stdout, "Table created successfully\n");
    }

    /* Create SQL statement */
    sqlstr="CREATE TABLE IF NOT EXISTS Datos (" \
           "No_Medida INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
           "Temp_prom REAL NOT NULL," \
           "Temp_max	REAL NOT NULL," \
           "Temp_min	REAL NOT NULL," \
           "Hum_prom	REAL NOT NULL," \
           "Hum_max REAL NOT NULL," \
           "Hum_min REAL NOT NULL," \
           "Vel_prom	REAL NOT NULL," \
           "Vel_max REAL NOT NULL," \
           "Vel_min REAL NOT NULL," \
           "DirV_prom REAL NOT NULL," \
           "DirV_max	REAL NOT NULL," \
           "DirV_min	REAL NOT NULL," \
           "Prec_prom REAL NOT NULL," \
           "Prec_max	REAL NOT NULL," \
           "Prec_min	REAL NOT NULL," \
           "IntL_prom REAL NOT NULL," \
           "IntL_max	REAL NOT NULL," \
           "IntL_min	REAL NOT NULL" \
           ");";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
       return (3);
    } else {
       fprintf(stdout, "Table created successfully\n");
    }

    /* Create SQL statement */
     sqlstr="CREATE TABLE IF NOT EXISTS Inicio (" \
            "U_Start TEXT NOT NULL," \
            "F_Start TEXT NOT NULL," \
            "H_Start TEXT NOT NULL" \
            ");";

     /* Execute SQL statement */
     rc = sqlite3_exec(db, sqlstr.c_str(), 0, 0, &zErrMsg);

     if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return (2);
     } else {
        fprintf(stdout, "Table created successfully\n");
     }
    sqlite3_close(db);
    return true;

}


bool Control_DB::cerrar_DB(){

    int rc = sqlite3_close( _db );

    if( rc != SQLITE_OK )
        return false;

    return true;
}

bool Control_DB::guardarDatos_DB(double Data[18]){
    char *mesg = 0;
    int rc = 0;
    stringstream sql;
    sql << "INSERT INTO Datos (Temp_prom, Temp_max, Temp_min, Hum_prom, Hum_max, Hum_min, Vel_prom, Vel_max, Vel_min, DirV_prom, DirV_max, DirV_min, Prec_prom, Prec_max, Prec_min, IntL_prom, IntL_max, IntL_min) VALUES (";
    sql << "'" << Data[0] << "', '" << Data[1] << "', '" << Data[2] << "', '" << Data[3] << "', '" << Data[4] << "', '" << Data[5] << "', '" << Data[6] << "', '" << Data[7] << "', '" << Data[8] << "', '" << Data[9] << "', '" << Data[10] << "', '" << Data[11] << "', '" << Data[12] << "', '" << Data[13] << "', '" << Data[14] << "', '" << Data[15] << "', '" << Data[16] << "', '" << Data[17] << "');" ;
    rc = sqlite3_exec( _db, sql.str().c_str(), 0, 0, &mesg );

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", mesg);
       sqlite3_free(mesg);
    }
    sql.str("");
    return true;
}

bool Control_DB::guardarUsuario_DB(string Us, string Con, string Nom, string Ape, string Doc, string FNac, int FT, int FH, int FV, int FD, int FP, int FI, int Cul)
{
    char *mesg = 0;
    int rc = 0;
    stringstream sql;
    sql << "INSERT INTO Usuarios (Usuario, Contraseña, Nombre, Apellido, Documento, Fecha_nac, f_Temp, f_Hum, f_Vel, f_Dir, f_Prec, f_Int, Cultivo) VALUES (";
    sql << "'" << Us << "', '" << Con << "', '" << Nom << "', '" << Ape << "', '" << Doc << "', '" << FNac << "', '" << FT << "', '" << FH << "', '" << FV << "', '" << FD << "', '" << FP << "', '" << FI << "', '" << Cul << "');" ;
    rc = sqlite3_exec( _db, sql.str().c_str(), 0, 0, &mesg );
    cout << sql.str() << endl;

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", mesg);
       sqlite3_free(mesg);
    } else {
       fprintf(stdout, "Records created successfully\n");
    }
    sql.str("");
    return true;
}

bool Control_DB::guardarInicio_DB(string uss)
{
    char *mesg = 0;
    int rc = 0;
    stringstream sql;
    sql.str("");
    sql << "INSERT INTO Inicio (U_Start, F_Start, H_Start, N_Dato) VALUES (";
    sql << "'" << uss << "', (SELECT date('now','localtime')), (SELECT time('now','localtime')), (SELECT MAX(No_medida) FROM Datos));" ;
    rc = sqlite3_exec( _db, sql.str().c_str(), 0, 0, &mesg );
    cout << sql.str() << endl;

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", mesg);
       sqlite3_free(mesg);
    } else {
       fprintf(stdout, "Records created successfully\n");
    }
    return true;
}
int Control_DB::rellenar_U (void* data, int argc, char *argv[], char *campos[]){
    int *ttemp = (int*)data;
    for (int i = 0; i < 7; i++ ){
        ttemp[i] = atoi(argv[i]);
    }
    return 0;
}
bool Control_DB::Comprobar_U(string Us, string Con, int D_Us[7]){
    char *mesg = 0;
    int rc = 0;

    int tmp[7]; // En este vector se traen los datos de la callback function.

    stringstream sql;
    sql << "SELECT f_Temp, f_Hum, f_Vel, f_Dir, f_Prec, f_Int, Cultivo FROM Usuarios WHERE Usuario ='" << Us << "' and Contraseña ='" << Con << "';";

    rc = sqlite3_exec( _db, sql.str().c_str(), rellenar_U, (void*)&tmp, &mesg);
    if (rc != SQLITE_OK ){
        return false;
    }
    D_Us[0] = tmp[0];
    D_Us[1] = tmp[1];
    D_Us[2] = tmp[2];
    D_Us[3] = tmp[3];
    D_Us[4] = tmp[4];
    D_Us[5] = tmp[5];
    D_Us[6] = tmp[6];
    sql.str("");

    return true;

}

int Control_DB::rellenar_Datos(void* data, int argc, char *argv[], char *campos[]){
    double *ttemp = (double*)data;
    for (int i = 0; i < 18; i++ ){
        ttemp[i] = atof(argv[i]);
    }
    return 0;
}
bool Control_DB::ObtenerDatos_DB(double Data[19])
{
    char *mesg = 0;
    int rc = 0;

    double tmp[18]; // En este vector se traen los datos de la callback function.
    stringstream sql;
    sql << "SELECT Temp_prom, Temp_max, Temp_min, Hum_prom, Hum_max, Hum_min, Vel_prom, Vel_max, Vel_min, DirV_prom, DirV_max, DirV_min, Prec_prom, Prec_max, Prec_min, IntL_prom, IntL_max, IntL_min FROM Datos WHERE No_Medida = (SELECT MAX(No_medida) FROM Datos)";

    rc = sqlite3_exec( _db, sql.str().c_str(), rellenar_Datos, (void*)&tmp, &mesg);
    if (rc != SQLITE_OK ){
        return false;
    }
    Data[0] = tmp[0], Data[1] = tmp[1], Data[2] = tmp[2], Data[3] = tmp[3];
    Data[4] = tmp[4], Data[5] = tmp[5], Data[6] = tmp[6], Data[7] = tmp[7];
    Data[8] = tmp[8], Data[9] = tmp[9], Data[10] = tmp[10], Data[11] = tmp[11];
    Data[12] = tmp[12], Data[13] = tmp[13], Data[14] = tmp[14], Data[15] = tmp[15];
    Data[16] = tmp[16], Data[17] = tmp[17];
    //cout <<"Temperatura: "<< Data[0]<<", Humedad: "<< Data[3]<< endl;
    sql.str("");

    return true;

}
int Control_DB::rellenar_Temp(void* data, int argc, char *argv[], char *campos[]){
    int *ttemp = (int*)data;
        ttemp[0] = atoi(argv[0]);
    return 0;
}
bool Control_DB::Promedio_T(int D_Ref)
{
    char *mesg = 0;
    int rc = 0;
    int Dia_calor = 0;

    int tmp[1]; // En este vector se traen los datos de la callback function.

    stringstream sql;
    sql << "SELECT AVG(Temp_prom) FROM Datos WHERE No_Medida > ((SELECT MAX (No_Medida) FROM Datos) -" << D_Ref << ")";

    rc = sqlite3_exec( _db, sql.str().c_str(), rellenar_Temp, (void*)&tmp, &mesg);
    if (rc != SQLITE_OK ){
        return false;
    }
    if (tmp[0] > 10) Dia_calor = 1;
    else Dia_calor = 0;

    sql.str("");

    return Dia_calor;

}
int Control_DB::rellenar_Dias(void* data, int argc, char *argv[], char *campos[]){
    int *ttemp = (int*)data;
    for (int i = 0; i < 2; i++ )
        ttemp[i] = atoi(argv[i]);
    return 0;
}
bool Control_DB::GuardarDia_DB(int Mal_dia, int Dia_calor, int Prueba)
{
    char *mesg = 0;
    int rc = 0;
    int tmp[2];
    stringstream sql;
    sql << "SELECT Día_malo_papa, Día_calor_rosa FROM Días WHERE No_día = (SELECT MAX(No_día) FROM Días);";
    rc = sqlite3_exec( _db, sql.str().c_str(), rellenar_Dias, (void*)&tmp, &mesg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", mesg);
       sqlite3_free(mesg);
    }
    if (Prueba < 1440){
        tmp[0] = 0;
        tmp[1] = 0;
    }
    if (Mal_dia == 1) tmp[0] ++;
    else tmp[0] = 0;
    if (Dia_calor == 1) tmp[1]++;
    else tmp[1] = 0;
    sql.str("");
    sql << "INSERT INTO Días (Día_malo_papa, Día_calor_rosa) VALUES (";
    sql << "'" << tmp[0] << "','" << tmp[1] << "');";
    rc = sqlite3_exec( _db, sql.str().c_str(), 0, 0, &mesg );

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", mesg);
       sqlite3_free(mesg);
    }
    sql.str("");
    return true;
}

bool Control_DB::ObtenerDias_DB(int Dias[2])
{
    char *mesg = 0;
    int rc = 0;
    int tmp[2];
    stringstream sql;
    sql << "SELECT Día_malo_papa, Día_calor_rosa FROM Días WHERE No_día = (SELECT MAX(No_día) FROM Días);";
    rc = sqlite3_exec( _db, sql.str().c_str(), rellenar_Dias, (void*)&tmp, &mesg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", mesg);
       sqlite3_free(mesg);
    }
    Dias[0] = tmp[0];
    Dias[1] = tmp[1];
    sql.str("");
    return true;}
Control_DB::Control_DB()
{

}


