/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameState.h
 * Author: jordi
 *
 * Created on 3 de mayo de 2017, 10:15
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include "hud.h"

class GameState {
public:
    GameState();
    void setEstado(GameState &est,int u);
    void render(sf::RenderWindow &window, hud *h,int u);
    virtual ~GameState();
private:

};




#endif /* GAMESTATE_H */

