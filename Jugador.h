
#include <iostream>
#include "cabecera.hpp"
#include "Animacion.h"
#include "Bala.h"
#include "Granada.h"

class Jugador {
public:
    Jugador(int anchura,int altura,string enlace);
    void Movimiento(Time &tiempo);
    void Saltar();
    void Disparar();
    void UpdateDisparo();
    void RenderDisparo(RenderWindow &window);
    RectangleShape getJugador();
    float getposX();
    float getposY();
    Vector2f getPos();
    Animacion getAnimacion();
    int getActual();
    int gettotalSpritesAnimacion();
    int getframeActual(Time &tiempo);
    void DispararGranada();
    
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
    std::vector<Bala*> CARGADOR;
    std::vector<Granada*> CARGADORGRANADA;
    sf::Texture TEX;
    float countBala;
    sf::Clock RelojBala;
    sf::Clock RelojGranada;
    float velocidadAnimacion;
    
};



