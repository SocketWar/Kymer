
#include <iostream>
#include "cabecera.hpp"
#include "Animacion.h"

class Jugador {
public:
    Jugador(int anchura,int altura,string enlace);
    void Movimiento(Time &tiempo);
    void Saltar();
    RectangleShape getJugador();
    float getposX();
    float getposY();
    Animacion getAnimacion();
    int getActual();
    int gettotalSpritesAnimacion();
    int getframeActual(Time &tiempo);
    
private:

    RectangleShape cuadrado;
    Vector2f tamanyo;
    Vector2f velocidad;//velocidad en las dos posiciones
    float velocidadmovimiento;
    float posX;
    float posY;
    float gravedad;
    int distanciasuelo;
    float velocidadsalto;
    //Animacion
    Animacion *animacion;
    int totalSpritesAnimacion;
    int actual;
    Vector2i posiciones;
    float velocidadanimacion;
    
};



