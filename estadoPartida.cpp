/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estadoPartida.cpp
 * Author: jordi
 * 
 * Created on 7 de mayo de 2017, 0:37
 */

#include "estadoPartida.h"
#include <sstream>
#include <SFML/Graphics.hpp>


estadoPartida::estadoPartida() {
}

void estadoPartida::render(sf::RenderWindow &window, hud *h){
    sf::Font font;
    if(!font.loadFromFile("res/font/comic.ttf")){
        std::cerr << "Error cargando la fuente";
        exit(0);
    }
    std::ostringstream partida;
    
    partida<<"polla";   
    sf::Text live(partida.str(),font);
    live.setString(partida.str());
    live.setPosition(500,20);
    live.setCharacterSize(22);
    live.setColor(sf::Color::Black);
    live.setStyle(sf::Text::Bold);
    
    window.draw(live);
    window.draw(h->getGranada());
}

estadoPartida::~estadoPartida() {
}

