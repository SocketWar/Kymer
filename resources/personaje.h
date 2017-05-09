/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   personaje.h
 * Author: darktom
 *
 * Created on April 3, 2017, 7:12 PM
 */

#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class personaje {
public:
    personaje(int numFrames,int spriteXanim[],Texture &tex);
    Sprite getSprite(int animacion,int pos);//pasara un rango del array a recorrer
//    void addSprite();
   void addSprite(int filas,int col,IntRect dim);
    int getNumAnimaciones();
    void setScale(int o);
private:
    Vector2f position;
    Sprite ***sprites;
    int cantAnim[];
    float speed;
    int numFotograma;
    int totalFotogramas;
    int fotogramaActivo;
    Clock reloj;
    
};

#endif /* PERSONAJE_H */

