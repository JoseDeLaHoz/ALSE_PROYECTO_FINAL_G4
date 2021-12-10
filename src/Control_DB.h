/**
 * @file Control_DB.h
 * @authors Juan Felipe Otálora, José Luis de la Hoz y Victor Daniel Escobar
 * @date 10/12/2021
 * @brief Aquí es donde se crean las funciones que se usarán en todo el programa las cuales se encargarán de todo el control de la base de datos.
 */

#ifndef CONTROL_DB_H
#define CONTROL_DB_H
#include <string>
#include <sqlite3.h>

using namespace std;
/**
 * @brief Definición de la clase Control_DB. Aquí se decide que partes de la clase serán públicas y por lo tanto se heredarán y que parte será privada.
 */
class Control_DB{

public:
    /**
     * @brief La función Control_DB es el constructor para crear un objeto tipo DB.
     * @param path
     */
    Control_DB(std::string path);
    /**
     * @brief La función abrir_DB esta es la encargada de abrir la base de datos.
     * @return No devuelve nada.
     */
    bool abrir_DB();
    /**
     * @brief La función crear_DB se encarga de crear la base de datos si no se cuenta con una previamente.
     * @return No devuelve nada.
     */
    bool crear_DB();
    /**
     * @brief La función cerrar_DB esta se encarga de cerrar la base de datos.
     * @return No devuelve nada.
     */
    bool cerrar_DB();
    /**
     * @brief La función guardarDatos_DB se encarga de guardar los siguientes promedios, máximos y mínimos en la base de datos.
     * @param Data
     * @return No devuelve nada.
     */
    bool guardarDatos_DB(double Data[18]);
    /**
     * @brief La función guardarUsuario_DB se encarga de guardar todos los datos personales y configuración básica de la toma de medida de los sensores relacionados con los usuarios, aqui se almacena el usuario, contraseña, nombre del usuario, apellido del usuario, documento de identidad, fecha de nacimiento, frecuencia de la toma de datos de los sensores y tipo de cultivo a revisar.
     * @param Us
     * @param Con
     * @param Nom
     * @param Ape
     * @param Doc
     * @param FNac
     * @param FT
     * @param FH
     * @param FV
     * @param FD
     * @param FP
     * @param FI
     * @param Cul
     * @return No devuelve nada.
     */
    bool guardarUsuario_DB(string Us, string Con, string Nom, string Ape, string Doc, string FNac, int FT, int FH, int FV, int FD, int FP, int FI, int Cul);
    /**
     * @brief La función guardarInicio_DB se encarga de guardar la fecha, hora, usuario y número de dato que inicio el programa.
     * @param uss
     * @return No devuelve nada.
     */
    bool guardarInicio_DB(string uss);
    /**
     * @brief La función Comprobar_U es la encargada de validar el usuario y la contraseña ingresada para de esta forma dar paso a la medición de los sensores.
     * @param Us
     * @param Con
     * @param D_Us
     * @return No devuelve nada.
     */
    bool Comprobar_U(string Us, string Con, int D_Us[7]);
    /**
     * @brief La función ObtenerDatos_DB se encarga de obteder los datos de la tabla datos.
     * @param Data
     * @return No devuelve nada.
     */
    bool ObtenerDatos_DB(double Data[18]);
    /**
     * @brief La función Promedio_T es la encargada de calcular el promedio de la temperatura del dia para de esta forma determinar si fue un mal dia en el caso del cultivo de papa o si fue un dia de calor en el caso del cultivo de rosas.
     * @param D_Ref
     * @return No devuelve nada.
     */
    bool Promedio_T(int D_Ref);
    /**
     * @brief La función GuardarDia_DB se encarga de llevar el registro de la temperatura del dia para de esta forma determinar si fue un mal dia en el caso del cultivo de papa o si fue un dia de calor en el caso del cultivo de rosas.
     * @param Mal_dia
     * @param Dia_calor
     * @param Prueba
     * @return No devuelve nada.
     */
    bool GuardarDia_DB(int Mal_dia, int Dia_calor, int Prueba);
    /**
     * @brief La funcion ObtenerDias_DB se encarga de obtiene el último dato de la tabla dias.
     * @param Dias
     * @return No devuelve nada.
     */
    bool ObtenerDias_DB(int Dias[2]);

private:
    sqlite3         *_db;
    std::string     _url;
    /**
     * @brief Es la función callback para la función rellenar_U.
     * @param data
     * @param argc
     * @param argv
     * @param campos
     * @return No devuelve nada.
     */
    static int rellenar_U (void* data, int argc, char *argv[], char *campos[]);
    /**
     * @brief Es la función callback para la función rellenar_Datos.
     * @param data
     * @param argc
     * @param argv
     * @param campos
     * @return No devuelve nada.
     */
    static int rellenar_Datos (void* data, int argc, char *argv[], char *campos[]);
    /**
     * @brief Es la función callback para la función rellenar_Temp.
     * @param data
     * @param argc
     * @param argv
     * @param campos
     * @return No devuelve nada.
     */
    static int rellenar_Temp(void *data, int argc, char *argv[], char *campos[]);
    /**
     * @brief Es la función callback para la funció rellenar_Dias.
     * @param data
     * @param argc
     * @param argv
     * @param campos
     * @return No devuelve nada.
     */
    static int rellenar_Dias(void *data, int argc, char *argv[], char *campos[]);

    Control_DB();

};
#endif // DB_LOCAL_H
