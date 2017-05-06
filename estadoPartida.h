/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estadoPartida.h
 * Author: jordi
 *
 * Created on 7 de mayo de 2017, 0:37
 */


#ifndef ESTADOPARTIDA_H
#define ESTADOPARTIDA_H
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "hud.h"

class estadoPartida: public GameState{
public:
    estadoPartida();
    void render(sf::RenderWindow &window, hud *h);
    virtual ~estadoPartida();
private:

};

#endif /* ESTADOPARTIDA_H */

