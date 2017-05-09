/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* t
 * File:   personaje.cpp
 * Author: darktom
 * 
 * Created on April 3, 2017, 7:12 PM
 */

#include "personaje.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

personaje::personaje(int totalAnimaciones,int spriteXanim[], Texture &tex) {
    this->numFotograma = 0;
    this->totalFotogramas = totalAnimaciones;
    this->sprites = new Sprite**[totalFotogramas];
    int asdf[totalFotogramas];
    this->cantAnim[totalFotogramas];
   /*creamos la matriz */
    
    for (int l = 0; l<totalFotogramas; l++){
        sprites[l] = new sf::Sprite*[totalFotogramas];
    }
    
    for(int f = 0 ; f< totalFotogramas;f++){
            
        for(int j = 0 ;j<spriteXanim[f];j++){
           sprites[f][j] = new sf::Sprite(tex);
           sprites[f][j]->setScale(4,4);
           sprites[f][j]->setTextureRect(IntRect(54*j,77*f, 54, 77));
           sprites[f][j]->setPosition(150,50);
           
        }
        this->cantAnim[f]=spriteXanim[f];
       

    }

    if(!sprites){
        cout<<"no se ha podido reservar"<<endl;
    }
    this->speed = 0.5f;
    this->reloj.restart();
    this->position.x = 300;//para cuando dibuje
    this->position.y = 250;
    
  
}

void personaje::addSprite(int fil , int col, IntRect dim) {
    this->sprites[fil][col]->setTextureRect(dim);
}

Sprite personaje::getSprite(int animacion ,int pos) {
    
    return *sprites[animacion][pos];
}

int personaje::getNumAnimaciones() {
    return this->totalFotogramas;
}

void personaje::setScale(int orientacion){
    int escala = 0;
    if(orientacion ==0){//miramos a la izq
        escala = -4;
    }
    else{
        escala = 4;
    }
     for(int f = 0 ; f<  this->totalFotogramas;f++){
                for(int j = 0 ;j< this->cantAnim[f]-1;j++){
                    sprites[f][j]->setScale(escala,4);
                }
            }
        
}


