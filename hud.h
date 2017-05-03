/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hud.h
 * Author: salva
 *
 * Created on 1 de mayo de 2017, 20:15
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hud.h
 * Author: javi
 *
 * Created on 29 de abril de 2017, 18:35
 */

#ifndef HUD_H
#define HUD_H
#include <iostream>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

class hud {
public:
    hud(sf::View &win);
    void setplayerHP();
    void setarmas();
    void setPosArma();
    void setText(sf::Text *&t, int x, int y, int size);
    void changeContHP(int i);
    void changePunt(int i);
    void changeArma(int i);
    void changeGranada(int i);
    void changeTime(int i);
    int getContHP();
    int getContGranada();
    void updateTime();
    sf::Sprite getPlayerHP(int i);
    sf::Sprite getIcono();
    sf::Sprite getArma();
    sf::Sprite getGranada();
    sf::Text getTextVida();
    sf::Text getTextArma();
    sf::Text getTextGranada();
    sf::Text getTextTime();
    sf::Text getTextPunt();
    
    void Update(sf::RenderWindow &win, sf::View &vista);

    int getPunt();
    virtual ~hud();
private:
    std::vector<sf::Sprite*> *armas;
    sf::Sprite *arma_actual;
    sf::Sprite *granada;
    std::vector<sf::Sprite*> *playerHP;
    sf::Sprite *icono;
    sf::Texture *tex;
    sf::Font *font;
    sf::Text *HPText;
    sf::Text *gunText;
    sf::Text *grenadeText;
    sf::Text *timeText;
    sf::Text *puntText;
    sf::Clock *c;
    std::ostringstream s;
    int time;
    int time_aux;
    int contHP;
    int contG;
    int contPunt;
    bool resol;
};

#endif /* HUD_H */

