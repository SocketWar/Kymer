/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menu.hpp
 * Author: darktom
 *
 * Created on May 7, 2017, 3:23 PM
 */

#ifndef SCREEN_0_HPP
#define SCREEN_0_HPP

#include <iostream>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Motor2D.h"
#include "sonido.h"
using namespace std;
using namespace sf;

class menu : public cScreen {
private:
    /* atenuacion de la pantalla*/
    int alpha_max;
    int alpha_div;
    
    bool playing;
    bool options;
    bool versus;
    bool comoJugar;
    bool spa;
    
    sonido *Sound;
    

public:
    menu(void);
    virtual int Run();
};


#endif /* SCREEN_0_HPP */
