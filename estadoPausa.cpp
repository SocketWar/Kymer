/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estadoPausa.cpp
 * Author: jordi
 * 
 * Created on 7 de mayo de 2017, 0:44
 */

#include "estadoPausa.h"
#include <sstream>


estadoPausa::estadoPausa() {
}

void estadoPausa::render(sf::RenderWindow &window, hud *h){
    sf::Font font;
    if(!font.loadFromFile("res/font/comic.ttf")){
        std::cerr << "Error cargando la fuente";
        exit(0);
    }
    std::ostringstream pausa;
    
    pausa<<"Pausa";   
    sf::Text live(pausa.str(),font);
    live.setString(pausa.str());
    live.setPosition(500,20);
    live.setCharacterSize(22);
    live.setColor(sf::Color::Black);
    live.setStyle(sf::Text::Bold);
    
    window.draw(live);
    window.draw(h->getArma());
}
estadoPausa::~estadoPausa() {
}

