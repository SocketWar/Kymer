#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include "cabecera.hpp"
#include "Animacion.h"
#include "Bala.h"
#include "Granada.h"
#include "Estado.h"
#include "sonido.h"
#include "Motor2D.h"

class Jugador {
public:
    Jugador(int anchura, int altura);
    void update(Time &tiempo);
    void render(float interpolacion,Time &tiempo);
    void Movimiento(Time &tiempo);
    void Saltar();
    void Disparar();
    void UpdateDisparo();
    void RenderDisparo(float interpolacion);
    RectangleShape getJugador();
    Vector2f getPos();
    Animacion getAnimacion();
    int getActual();
    int gettotalSpritesAnimacion();
    int getframeActual(Time &tiempo);
    void actualizarEstado();
    void setEstado();
    void Morir();
    Estado* getViejo();
    Estado* getNuevo();
    void setVidas(int i);
    int getVidas();
    void setGranadas(int i);
    int getGranadas();
    void setArma(int i);
    int getArma();
    sonido getSonido();
    void actualizarHitbox();
    void calcularColision(FloatRect** arrayColisiones,int nobjetos);
    RectangleShape gethitBox();
private:

    Vector2f velocidad; //velocidad en las dos posiciones
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
    int vidas;
    int granadas;
    int arma;
    sonido *soundEffect;
    bool suelo;
    bool colision;
    bool estadocolision;
    bool muro;
    //colisiones
    RectangleShape hitBox;
    RectangleShape trol;
    RectangleShape trol2;
    
    //interpolacion
    Estado *viejo;
    Estado *nuevo;
};


#endif /* JUGADOR_H */
