

#ifndef ANIMACION_H
#define ANIMACION_H

#include <iostream>
#include "cabecera.hpp"

class Animacion {
public:
    Animacion(string tex);
    void spritePersonaje(char l);
    int* getNumAnimaciones();
    Sprite getSprite(int animacion ,int pos);
    void orientacion(int orientacion);
    Sprite getSpriteE();
    int getOrientacion(){ return ORIENTACION;};
    void Movimiento(Vector2f vector);
    void MovimientoInterpolado(Vector2f vector);
private:
    Texture *tex;
    int *animacion;
    Sprite ***sprites;
    float speed;
    int numFotograma;
    int totalFotogramas;
    int fotogramaActivo;
    float escala;
    int ORIENTACION;
};

#endif /* ANIMACION_H */

