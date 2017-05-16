
#ifndef BALA_H
#define BALA_H

#include <SFML/Graphics.hpp>
#include "Estado.h"
using namespace sf;

class Bala {
public:
    //Bala(int h, int w, float *sp, int dist);
    Bala(int h, int w, float spX,float spY, int dist);
    void setPosition(float xStart, float yStart);
    void loadSprite(Texture textura, int posX, int posY);
    int move();
    bool colision(Rect<float> hit);
    virtual ~Bala();
    int getHeigth(){ return HEIGTH;}
    int getWidth(){ return WIDTH;}
    int getSpeedX(){ return SPEEDX;}
    int getSpeedY(){ return SPEEDY;}
    //float getSpeed(){ return *SPEED;}
    int getTiempo(){ return TIEMPO;}
    float getX(){ return X;}
    float getY(){ return Y;}
    Sprite getSprite(){ return *SPRITE;}
    Texture getTexture(){return *TEX;}
    Rect<float> getHitbox(){return *HITBOX;}
    Estado* getViejo();
    Estado* getNuevo();
    void actualizarEstado();
    
protected:
    int HEIGTH;
    int WIDTH;
    //float *SPEED[2];
    float SPEEDX;
    float SPEEDY;
    int TIEMPO;
    float YTIEMPO;
    float X,Y;
    Texture *TEX;
    Sprite *SPRITE;
    Rect<float> *HITBOX;
    Estado *viejo;
    Estado *nuevo;

};

#endif /* BALA_H */

