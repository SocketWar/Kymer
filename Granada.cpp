/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Granada.cpp
 * Author: jordi
 * 
 * Created on 27 de marzo de 2017, 19:38
 */

#include "Granada.h"
#include <math.h>


//Bala::Bala(int h, int w, float *sp, int dist)
Granada::Granada(int h, int w, float spX,float spY, int dist)
{
   
    TEX = new Texture();
    SPRITE = new Sprite();
    HITBOX = new Rect<float>();
    HEIGTH=h;
    WIDTH=w;
    SPEEDX=spX;
    SPEEDY=spY;
    TIEMPO=dist;
    X=300;
    Y=100;
    Reloj = new Clock();
}


void Granada::setPosition(float xStart,float yStart){
    X=xStart;
    Y=yStart;
    SPRITE->setPosition(xStart,yStart);
    HITBOX = new Rect<float> (X,Y,WIDTH,HEIGTH);
}

void Granada::loadSprite(Texture textura, int posX, int posY){
    *TEX= textura;
    *SPRITE=Sprite(*TEX);
    SPRITE->setOrigin(0,0);
    SPRITE->setTextureRect(IntRect(posX,posY,WIDTH,HEIGTH));
    if(SPEEDX<0)
        SPRITE->scale(-1,1);
    if(SPEEDY>0)
        SPRITE->rotate(90);
    if(SPEEDY<0)
        SPRITE->rotate(270);
}
/*
 * Si devuelve 1, avanza
 * Si devuelve 2, acaba su recorrido
 * Si devuelve -1, error
 */
int Granada::move(){
    if(TIEMPO!=0){
        X+=SPEEDX;
        float a=20.8f;
        Y+=(-SPEEDY+((a*Reloj->getElapsedTime().asSeconds()))*Reloj->getElapsedTime().asSeconds());
        HITBOX->left=X;
        HITBOX->top=Y;
        SPRITE->setPosition(X,Y);
        TIEMPO-=1;
        return 1;
    }else{
        return 2;
    }
    return -1;
}

bool Granada::colision(Rect<float> hit){
    if(HITBOX->intersects(hit)){
        HITBOX->height=HITBOX->height*4;
        HITBOX->width=HITBOX->width*4;
    }
    return HITBOX->intersects(hit);
}

Granada::~Granada() {
    delete TEX;
    delete SPRITE;
    delete HITBOX;
    delete Reloj;
}