#include "sensor.h"


void Sensor::actualizar(int contador, int periodo){
    if (contador % periodo == 0){
        _dato = ( (rand() % _limite) + _vmin);
        _acum += _dato;
        _cant++;}
    if (_dato > _max) _max = _dato;
    if (_dato < _min) _min = _dato;
}

void Sensor::reiniciar() {
    _acum = 0;
    _dato = 0;
    _max = -3000;
    _min = 3000;
    _conteo = 0;
    _cant = 0;
}
