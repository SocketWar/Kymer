/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameState.cpp
 * Author: jordi
 * 
 * Created on 3 de mayo de 2017, 10:15
 */

#include "GameState.h"
#include "estadoPartida.h"
#include "estadoPausa.h"
#include <SFML/Graphics.hpp>

GameState::GameState() {
}

void GameState::setEstado(GameState &est, int u){
    if (u == 1){
        //est = new estadoPartida();
    }
    if (u==2){
        //est = new estadoPausa();
    }
}

void GameState::render(sf::RenderWindow &window, hud *h, int u){
    if (u == 1){
        estadoPartida *e = new estadoPartida();
        e->render(window,h);
    }
    if (u==2){
        estadoPausa *e = new estadoPausa();
        e->render(window,h);
    }
}

GameState::~GameState() {
}

