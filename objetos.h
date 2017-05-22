

#ifndef OBJETOS_H
#define OBJETOS_H

#include "Motor2D.h"



#include "sonido.h"
#include <SFML/Graphics.hpp>

class objetos {
public:
    objetos(int i, float x, float y);
    virtual ~objetos();
    Vector2f getPos();
    void RenderObjeto();//para mostrar por pantalla
    Vector2f getSize();
    void reproducirSonido();
    Sprite getSprite();
    void setDestruir();
    bool getDestruir();
    char getTipo();
private:
    Texture *tex;
    Sprite *sprite;
    bool tocado;
    Vector2f pos;
    Vector2f size;
    sonido *Sound;
    int tipo;
    bool DESTRUIR;

};

#endif /* OBJETOS_H */

