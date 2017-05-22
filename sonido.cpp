/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sonido.cpp
 * Author: darktom
 * 
 * Created on May 13, 2017, 8:20 PM
 */

#include "sonido.h"

sonido::sonido() {
    //reservar memoria
    buffer = new SoundBuffer();
    sound = new Sound();
}

void sonido::setSonido(string ruta){
    
    if(!buffer->loadFromFile(ruta)){
        cout<<"error: no se encuentra el sonido: "<<ruta<<endl;
    }
    sound->setBuffer(*buffer);
    
}
Sound sonido::getSonido(){
    return *sound;
}

void sonido::reproducir() {
    this->sound->play();
}

void sonido::setVolumen(float v){
    sound->setVolume(v);
}

bool sonido::comprobarReproduccion() {
    return this->sound->Playing;
}

int sonido::getReproduccion() {
    return reprod;
}

void sonido::setReproduccion(int n) {
    reprod = n;
}


