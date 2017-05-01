/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjetoPuntuacion.cpp
 * Author: salva
 * 
 * Created on 1 de mayo de 2017, 20:26
 */

#include <SFML/Graphics/Sprite.hpp>

#include "ObjetoPuntuacion.h"
#include "hud.h"

ObjetoPuntuacion::ObjetoPuntuacion(sf::Texture *tex, int x, int y, int h, int w, int pun) {
    recogido = false;
    puntos = pun;
    posX = x;
    posY = y;
    height = h;
    width = w;
    sprite = new sf::Sprite(*tex);
    sprite->setOrigin(0,0);
    sprite->setTextureRect(sf::IntRect(x,y,h,w));
    sprite->setPosition(x,y);
    hitbox = new sf::Rect<float>(x,y,h,w);
}

void ObjetoPuntuacion::recogerObjeto(){
    delete hitbox;
    recogido = true;
}

int ObjetoPuntuacion::getPuntos(){
    return puntos;
}

sf::Sprite ObjetoPuntuacion::getSprite(){
    return *sprite;
}

bool ObjetoPuntuacion::getRecogido(){
    return recogido;
}

sf::Rect<float> ObjetoPuntuacion::getHitbox(){
    return *hitbox;
}

ObjetoPuntuacion::~ObjetoPuntuacion() {
}

