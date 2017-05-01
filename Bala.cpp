

#include "Bala.h"

Bala::Bala(int h, int w, float spX,float spY, int dist)
{
   
    TEX = new Texture();
    SPRITE = new Sprite();
    HITBOX = new Rect<float>();
    HEIGTH=h;
    WIDTH=w;
    //*SPEED[0]=*sp[0];
    //*SPEED[1]=*sp[1];
    SPEEDX=spX;
    SPEEDY=spY;
    TIEMPO=dist;
    X=300;
    Y=100;
}


void Bala::setPosition(float xStart,float yStart){
    X=xStart;
    Y=yStart;
    SPRITE->setPosition(xStart,yStart);
    HITBOX = new Rect<float> (X,Y,WIDTH,HEIGTH);
}

void Bala::loadSprite(Texture textura, int posX, int posY){
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
int Bala::move(){
    if(TIEMPO!=0){
        X+=SPEEDX;
        Y+=SPEEDY;
        HITBOX->left=X;
        HITBOX->top=Y;
        TIEMPO-=1;
        YTIEMPO+=0.1f;
        SPRITE->setPosition(X,Y);
        return 1;
    }else{
        return 2;
    }
    return -1;
}

bool Bala::colision(Rect<float> hit){
    return HITBOX->intersects(hit);
}

Bala::~Bala() {
    delete TEX;
    delete SPRITE;
    delete HITBOX;
}

