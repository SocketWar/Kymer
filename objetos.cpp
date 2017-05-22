/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   objetos.cpp
 * Author: darktom
 * 
 * Created on May 18, 2017, 5:28 PM
 */

#include "objetos.h"

objetos::objetos(int i, float x, float y) {
    if (i == 0) {//arma
        Sound = new sonido();
        Sound->setSonido("res/audio/heavyMachine.wav");
        tex = new Texture();
        if (!tex->loadFromFile("res/img/heavyMachineGun.png")) {
            cout << "Error cargando la textura de objeto escopeta" << endl;

        }
        size = Vector2f(31, 30);
    } else if (i == 1) {//vidas
        Sound = new sonido();
        Sound->setSonido("res/audio/hp.wav");
        tex = new Texture();
        if (!tex->loadFromFile("res/img/obj_hp.png")) {
            cout << "Error cargando la textura de objeto vida" << endl;
        }
        size = Vector2f(31, 31);
    }else if (i==2){
        Sound = new sonido();
        Sound->setSonido("res/audio/coin.wav");
        tex = new Texture();
        if (!tex->loadFromFile("res/img/obj_punt.png")) {
            cout << "Error cargando la textura de objeto puntuacion" << endl;
        }
        size = Vector2f(31, 31);
    }else if (i==3){
        tex = new Texture();

        if (!tex->loadFromFile("res/img/obj_granada.png")) {
            cout << "Error cargando la textura de objeto granada" << endl;
        }
        size = Vector2f(31, 31);
    }
    tipo = i;
    pos = Vector2f(x, y);
    sprite = new Sprite(*tex);
    sprite->setTextureRect(IntRect(0, 0, size.x, size.y));
    sprite->setPosition(pos);
    tocado = false;
    DESTRUIR = false;


}

Vector2f objetos::getPos() {
    return pos;
}

Vector2f objetos::getSize() {
    return size;
}

void objetos::RenderObjeto() {/*renderizado basico para mostrar objeto por pantalla*/

    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& Window = motor->getWindow();
    Window.draw(*sprite);


}

void objetos::reproducirSonido() {
    // cout<<"reproducir sonido"<<endl;
    Sound->reproducir();
}

Sprite objetos::getSprite() {
    return *sprite;
}
char objetos::getTipo(){
    return tipo;
}

void objetos::setDestruir(){
    DESTRUIR=true;
}
bool objetos::getDestruir(){
    return DESTRUIR;
}

objetos::~objetos(){
    delete tex;
    delete sprite;
    delete Sound;
}