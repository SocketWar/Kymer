
#include <iostream>
#include "cabecera.hpp"

class Jugador {
public:
    Jugador(int anchura,int altura);
    void Movimiento(Time &tiempo);
    void Saltar();
    RectangleShape getJugador();
    float getposX();
    float getposY();
    
private:

    RectangleShape cuadrado;
    Vector2f tamanyo;
    Vector2f velocidad;
    float velocidadm;
    float posX;
    float posY;
    float gravedad;
    int distanciasuelo;
    float velocidadsalto;
};



