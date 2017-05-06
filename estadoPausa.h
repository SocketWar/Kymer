/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estadoPausa.h
 * Author: jordi
 *
 * Created on 7 de mayo de 2017, 0:44
 */

#ifndef ESTADOPAUSA_H
#define ESTADOPAUSA_H
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "hud.h"

class estadoPausa: public GameState{
public:
    estadoPausa();
    void render(sf::RenderWindow &window, hud *h);
    virtual ~estadoPausa();
private:

};

#endif /* ESTADOPAUSA_H */

