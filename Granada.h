
#ifndef GRANADA_H
#define GRANADA_H
#include "mapaTmx.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Granada{
public:
    Granada(int h, int w, float spX,float spY, int dist);
    void setPosition(float xStart, float yStart);
    void loadSprite(Texture textura, int posX, int posY);
    int move();
    void spriteMortero();
    bool colision(Rect<float> hit);
    void explota(FloatRect *arrayColisiones);
    void setDimensiones(int w,int h);
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
    Estado* getViejo();
    Estado* getNuevo();
    void actualizarEstado();
    
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
    Estado *viejo;
    Estado *nuevo;
    bool explosion;
    bool mortero;
};

#endif /* GRANADA_H */

