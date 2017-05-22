

#ifndef OBJETOS_H
#define OBJETOS_H

#include "Motor2D.h"



#include "sonido.h"
#include <SFML/Graphics.hpp>

class objetos {
public:
    objetos(int i, float x, float y);
    Vector2f getPos();
    void RenderObjeto();//para mostrar por pantalla
    Vector2f getSize();
    void reproducirSonido();
    Sprite getSprite();
    char getTipo();
private:
    Texture *tex;
    Sprite *sprite;
    bool tocado;
    Vector2f pos;
    Vector2f size;
    sonido *Sound;
    int tipo;

};

#endif /* OBJETOS_H */

