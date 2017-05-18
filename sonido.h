/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sonido.h
 * Author: darktom
 *
 * Created on May 13, 2017, 8:20 PM
 */

#ifndef SONIDO_H
#define SONIDO_H

#include <iostream>
#include "cabecera.hpp"
#include <SFML/Audio.hpp>

class sonido {
public:
    sonido();
    void setSonido(string ruta);
    Sound getSonido();
    void reproducir();
    
private:
    SoundBuffer *buffer;
    Sound *sound;
};

#endif /* SONIDO_H */

