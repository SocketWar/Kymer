
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
    Vector2f getPos();
    Animacion getAnimacion();
    int getActual();
    int gettotalSpritesAnimacion();
    int getframeActual(Time &tiempo);
    void DispararGranada();
    
private:

    Vector2f velocidad;//velocidad en las dos posiciones
    float velocidadmovimiento;
    float gravedad;
    int distanciasuelo;
    float velocidadsalto;
    //Animacion
    Animacion *animacion;
    int totalSpritesAnimacion;
    int actual;
    float velocidadanimacion;
    std::vector<Bala*> CARGADOR;
    std::vector<Granada*> CARGADORGRANADA;
    sf::Texture TEX;
    sf::Texture TEX2;
    float countBala;
    sf::Clock RelojBala;
    sf::Clock RelojGranada;
    float velocidadAnimacion;
    
};



