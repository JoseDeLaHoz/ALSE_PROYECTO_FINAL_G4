/**
 * @file sensor.h
 * @author Juan Felipe Otálora, José Luis de la Hoz y Victor Daniel Escobar
 * @date 10/12/2021
 * @brief Aquí es donde se crean las funciones que se usarán en todo el programa las cuales se encargarán de generar y calcular todos los datos que se mostrarán relacionados con los sensores.
 */


#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

/**
 * @brief Definición de la clase Sensor. Aquí se define las variables y métodos tanto privados como públicos.
 */
class Sensor{

private:
    /**
     * @brief _dato es la variable donde se almacenarán los datos generados aleatoriamente.
     */
    double _dato;
    /**
     * @brief _limite es la variable que almacena los límites de la medidas de los sensores.
     */
    int _limite;
    /**
     * @brief _max es la variable que almacena el valor máximo del sensor.
     */
    double _max;
    /**
     * @brief _min es la variable que almacena el valor mínimo del sensor.
     */
    double _min;
    /**
     * @brief _acum es la variable que guarda el acomulado de los datos para calcular el promedio cada minuto.
     */
    double _acum;
    /**
     * @brief _cant es la varible que guarda la cantidad de datos generada por minutos.
     */
    int _cant;
    /**
     * @brief _periodo es la variable que almacena el periodo en el que se generarán los datos de los sensores.
     */
    int _periodo;

    int _conteo;
    /**
     * @brief _vmin es la variable que guarda el valor mínimo del randomizador.
     */
    int _vmin;

public:
    /**
     * @brief La función Sensor la cual se encarga de inicializar los sensores.
     * @param limite
     * @param vmin
     * @param periodo
     * @param dato
     * @param max
     * @param min
     * @param acum
     * @param cant
     */
    Sensor(int limite = 0, int vmin = 0, int periodo = 0, double dato = 0., double max = -3000, double min = 3000, double acum = 0, int cant = 0){
        _dato = dato;
        _limite = limite;
        _periodo = periodo;
        _acum = acum;
        _max = max;
        _min = min;
        _cant = cant;
        _vmin = vmin;
    }
    /**
     * @brief La función leerDato es de prueba la cual devuelve el valor del randomizador.
     * @return la variable _dato
     */
    double leerDato(){ return _dato; }
    /**
     * @brief La función actualizar la cual se encarga de revisar si el sensor debe volver a ejecutar el randomizador y además devuelve el máximo, el mínimo y el acumulado.
     * @param contador
     * @param periodo
     */
    void actualizar(int contador, int periodo);
    /**
     * @brief La función prom se encarga de ir calculado el promedio de las mediciones de los sensores dependiendo la frecuencia deseada por el usuario.
     * @return
     */
    double prom () {return _acum/_cant;}
    /**
     * @brief La función maximo la cual se encarga de retornar el valor máximo que hayan medido los sensores.
     * @return El valor máximo de los sensores.
     */
    double maximo () {return _max;}
    /**
     * @brief La función minimo la cual se encarga de retornar el valor mínimo que hayan medido los sensores.
     * @return EL valor mínimo de los sensores.
     */
    double minimo () {return _min;}
    /**
     * @brief La función reiniciar se encarga de reiniciar las variables relacionadas con el randomizador.
     */
    void reiniciar ();

};
/**
 * @brief Definición de la clase Temperatura la cual tendrá pública la función Temperatura ya que está la va a heredar.
 */
class Temperatura: public Sensor{
public:
    /**
     * @brief La función Temperatura la cual se apoya en la clase Sensor para generar datos aleatorios del sensor de temperatura el cual se encuentra entre -10 y 45 grados Celcius.
     */
    Temperatura():Sensor(55, -10){}
};
/**
 * @brief Definición de la clase Humedad a cual tendrá pública la función Humedad ya que está la va a heredar.
 */
class Humedad: public Sensor{
public:
    /**
     * @brief La función Humedad la cual se apoya en la clase Sensor para generar datos aleatorios del sensor de humedad el cual se encuentra entre 0 y 100 porciento.
     */
    Humedad():Sensor(100, 0){}
};
/**
 * @brief Definición de la clase Velocidad la cual tendrá pública la función Velocidad ya que está la va a heredar.
 */
class Velocidad: public Sensor{
public:
    /**
     * @brief La función Velocidad la cual se apoya en la clase Sensor para generar datos aleatorios del sensor de velocidad del viento el cual se encuentra entre 0 y 40 metros por segundo.
     */
    Velocidad():Sensor(40, 0){}
};
/**
 * @brief Definición de la clase DViento la cual tendrá pública la función DViento ya que está la va a heredar.
 */
class DViento: public Sensor{
public:
    /**
     * @brief La función DViento la cual se apoya en la clase Sensor para generar datos aleatorios del sensor de dirección del viento el cual se encuentra entre -180° y 180° Norte.
     */
    DViento():Sensor(360, -180){}
};
/**
 * @brief Definición de la clase Precipitacion la cual tendrá pública la función Precipitacion ya que está la va a heredar.
 */
class Precipitacion: public Sensor{
public:
    /**
     * @brief La función Precipitacion la cual se apoya en la clase Sensor para generar datos aleatorios del sensor de precipitación el cual se encuentra entre 0 y 50 milímetros.
     */
    Precipitacion():Sensor(50, 0){}
};
/**
 * @brief Definición de la clase Intensidad la cual tendrá pública la función Intensidad ya que está la va a heredar.
 */
class Intensidad: public Sensor{
public:
    /**
     * @brief La función Intensidad la cual se apoya en la clase Sensor para generar datos aleatorios del sensor de intensidad lumínica el cual se encuentra entre 0 y 2000 lumen.
     */
    Intensidad():Sensor(2000, 0){}
};

#endif // SENSOR_H
