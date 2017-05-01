
#ifndef GRANADA_H
#define GRANADA_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Granada{
public:
    Granada(int h, int w, float spX,float spY, int dist);
    void setPosition(float xStart, float yStart);
    void loadSprite(Texture textura, int posX, int posY);
    int move();
    bool colision(Rect<float> hit);
    virtual ~Granada();
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
    
private:
    int HEIGTH;
    int WIDTH;
    float SPEEDX;
    float SPEEDY;
    int TIEMPO;
    float X,Y;
    Texture *TEX;
    Sprite *SPRITE;
    Rect<float> *HITBOX;
    sf::Clock *Reloj;
};

#endif /* GRANADA_H */

