#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include "cabecera.hpp"
#include "Animacion.h"
#include "Bala.h"
#include "Granada.h"
#include "Estado.h"

class Jugador {
public:
    Jugador(int anchura, int altura);
    void Movimiento(Time &tiempo);
    void Saltar();
    void Disparar();
    void UpdateDisparo();
    void RenderDisparo(RenderWindow &window);
    Vector2f getPos();
    Animacion getAnimacion();
    int getActual();
    int gettotalSpritesAnimacion();
    int getframeActual(Time &tiempo);
    void DispararGranada();
    void actualizarEstado();
    void setEstado();
    void actualizarHeatbox();
    Estado* getViejo();
    Estado* getNuevo();
    void setVidas(int i);
    int getVidas();
    void calcularColision(FloatRect** arrayColisiones,int nobjetos);
    RectangleShape gethitBox();
    
private:

    Vector2f velocidad; //velocidad en las dos posiciones
    float velocidadmovimiento;
    float gravedad;
    float distanciasuelo;
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
    int vidas;
    //interpolacion
    Estado *viejo;
    Estado *nuevo;
    bool suelo;
    bool colision;
    bool estadocolision;
    //colisiones
    RectangleShape hitBox;
};


#endif /* JUGADOR_H */
