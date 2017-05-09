/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjetoPuntuacion.h
 * Author: salva
 *
 * Created on 1 de mayo de 2017, 20:26
 */

#ifndef OBJETOPUNTUACION_H
#define OBJETOPUNTUACION_H

class ObjetoPuntuacion {
public:
    ObjetoPuntuacion(sf::Texture *tex, int x, int y, int h, int w, int pun);
    sf::Sprite getSprite();
    bool getRecogido();
    sf::Rect<float> getHitbox();
    void recogerObjeto();
    int getPuntos();
    virtual ~ObjetoPuntuacion();
private:
    sf::Sprite *sprite;
    sf::Rect<float> *hitbox;
    int posX;
    int posY;
    int height;
    int width;
    int puntos;
    bool recogido;

};

#endif /* OBJETOPUNTUACION_H */

