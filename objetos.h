

#ifndef OBJETOS_H
#define OBJETOS_H

#include "Motor2D.h"



#include "sonido.h"
#include <SFML/Graphics.hpp>

class objetos {
public:
    objetos(char i, float x, float y);
    Vector2f getPos();
    void RenderObjeto();//para mostrar por pantalla
    Vector2f getSize();
    void reproducirSonido();
    Sprite getSprite();
private:
    Texture *tex;
    Sprite *sprite;
    bool tocado;
    Vector2f pos;
    Vector2f size;
    sonido *Sound;

};

#endif /* OBJETOS_H */

