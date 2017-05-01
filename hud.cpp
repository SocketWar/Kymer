/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hud.cpp
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
 * File:   hud.cpp
 * Author: javi
 * 
 * Created on 29 de abril de 2017, 18:35
 */

#include "hud.h"

hud::hud(sf::Texture *hTex, sf::Font *f, sf::RenderWindow &win) {
    resol = false;
    if (win.getSize().x < 1000)
        resol = true;

    tex = hTex;
    playerHP = new std::vector<sf::Sprite*>(6);

    icono = new sf::Sprite(*tex);
    icono->setOrigin(0, 0);
    if (resol) {
        icono->scale(0.85, 0.85);
    }
    icono->setTextureRect(sf::IntRect(180, 12, 95, 95));
    icono->setPosition(15, 10);

    granada = new sf::Sprite(*tex);


    granada->setOrigin(0, 0);
    granada->setTextureRect(sf::IntRect(280, 35, 70, 75));
    if (resol) {
        granada->scale(0.4, 0.4);
        granada->setPosition(200, 110);
    } else {
        granada->scale(0.5, 0.5);
        granada->setPosition(270, 110);
    }


    armas = new std::vector<sf::Sprite*>(2);


    c = new sf::Clock();
    contPunt = 0;
    contG = 0;
    contHP = 3;
    time = 30;
    font = f;
    time_aux = 0;
    
    s << "";

    if (!resol) {
        setText(HPText, 120, 1, 28);
        setText(gunText, 20, 110, 22);
        setText(grenadeText, 260, 110, 22);
        setText(puntText, win.getSize().x / 1.35, 25, 34);
        setText(timeText, (win.getSize().x / 2) - 50, 25, 34);
    } else {
        setText(HPText, 120, 1, 22);
        setText(gunText, 20, 110, 16);
        setText(grenadeText, 200, 110, 16);
        setText(puntText, win.getSize().x / 1.55, 5, 28);
        setText(timeText, (win.getSize().x / 2) - 100, 5, 28);
    }


    s.str(std::string());
    s << "         (x" << contG << ")";
    grenadeText->setString(s.str());
    s << "";



}

void hud::setText(sf::Text *&t, int x, int y, int size) {
    t = new sf::Text();
    t->setFont(*font);
    t->setString(s.str());
    t->setPosition(x, y);
    t->setCharacterSize(size);
    t->setColor(sf::Color::Yellow);
    t->setStyle(sf::Text::Bold);
}

void hud::setplayerHP() {
    float cont = 115.0f;

    for (int j = 0; j < 6; j++) {
        playerHP->at(j) = new sf::Sprite(*tex);
        playerHP->push_back(playerHP->at(j));
        playerHP->at(j)->setOrigin(0, 0);
        playerHP->at(j)->setTextureRect(sf::IntRect(40, 10, 85, 85));

        playerHP->at(j)->setPosition(cont, 30);
        if (resol == false) {
            playerHP->at(j)->scale(0.65, 0.65);
            cont = cont + 55.0f;
        } else {
            playerHP->at(j)->scale(0.50, 0.50);
            cont = cont + 40.0f;
        }

    }
    s.str(std::string());
    s << "Vidas: ";
    HPText->setString(s.str());

}

void hud::setarmas() {
    armas->at(0) = new sf::Sprite(*tex);
    armas->push_back(armas->at(0));
    armas->at(0)->setOrigin(0, 0);
    if (resol == false) {
        armas->at(0)->scale(0.65, 0.65);
    } else {
        armas->at(0)->scale(0.50, 0.50);
    }
    armas->at(0)->setTextureRect(sf::IntRect(30, 100, 100, 100));
    arma_actual = armas->at(0);
    setPosArma();

    s.str(std::string());
    s << "Arma: Pistola";
    gunText->setString(s.str());

    armas->at(1) = new sf::Sprite(*tex);
    armas->push_back(armas->at(1));
    armas->at(1)->setOrigin(0, 0);
    if (resol == false) {
        armas->at(1)->scale(0.6, 0.6);
    } else {
        armas->at(1)->scale(0.45, 0.45);
    }
    armas->at(1)->setTextureRect(sf::IntRect(170, 115, 170, 100));
}

void hud::updateTime() {
    if (time < 300) {

        time = time_aux + c->getElapsedTime().asSeconds();
    }
}

void hud::changeContHP(int i) {
    if (i >= 0 && i < 7) {
        contHP = i;
        s.str(std::string());
        s << "Vidas: ";
        HPText->setString(s.str());
    }
}

void hud::changePunt(int i) {
    if (i >= 0) {
        contPunt = i;
        s.str(std::string());
        s << "Puntuacion: " << contHP;
        puntText->setString(s.str());
    }
}

void hud::changeArma(int i) {
    if (i == 0 || i == 1) {
        arma_actual = armas->at(i);
        setPosArma();
        s.str(std::string());
        if (i == 0) {
            s << "Arma: Pistola";
        } else {
            s << "Arma: Metralleta";
        }
        gunText->setString(s.str());

    }
}

void hud::changeGranada(int i) {
    if (i >= 0) {
        contG = i;
        s.str(std::string());
        s << "         (x" << contG << ")";
        grenadeText->setString(s.str());
    }
}

void hud::changeTime(int i) {
    time = i;
    time_aux = time;
    c->restart();
}

void hud::setPosArma() {

    arma_actual->setPosition(20, 135);
}

int hud::getContHP() {
    return contHP;

}

int hud::getContGranada() {
    return contG;
}

sf::Sprite hud::getPlayerHP(int i) {
    return *playerHP->at(i);
}

sf::Sprite hud::getArma() {
    return *arma_actual;
}

sf::Sprite hud::getIcono() {
    return *icono;
}

sf::Text hud::getTextVida() {
    return *HPText;
}

sf::Text hud::getTextArma() {

    return *gunText;
}

sf::Text hud::getTextTime() {
    s.str(std::string());
    s << "Tiempo: " << time;
    timeText->setString(s.str());
    return *timeText;
}

sf::Text hud::getTextPunt() {
    s.str(std::string());
    s << "Puntuacion: " << contPunt;
    puntText->setString(s.str());
    return *puntText;
}

int hud::getPunt() {
    return contPunt;
}

sf::Sprite hud::getGranada() {
    return *granada;
}

sf::Text hud::getTextGranada() {
    return *grenadeText;
}

hud::~hud() {
    delete armas;
    delete arma_actual;
    delete granada;
    delete playerHP;
    delete icono;
    delete tex;
    delete font;
    delete HPText;
    delete gunText;
    delete grenadeText;
    delete timeText;
    delete puntText;
    delete c;

    armas = NULL;
    arma_actual = NULL;
    granada = NULL;
    playerHP = NULL;
    icono = NULL;
    tex = NULL;
    font = NULL;
    HPText = NULL;
    gunText = NULL;
    grenadeText = NULL;
    timeText = NULL;
    puntText = NULL;
    c = NULL;
}

