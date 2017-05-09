/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cScreen.hpp
 * Author: darktom
 *
 * Created on May 7, 2017, 3:17 PM
 */

#ifndef CSCREEN_HPP
#define CSCREEN_HPP

#include "Estado.h"



class cScreen
{
public :
    virtual int Run (sf::RenderWindow &App) = 0;
//     float InterpolacionRenderx(Estado& Anterior, Estado& Nuevo, float interpolacion) {
//
//        float movimientox = Anterior.getx()*(1 - interpolacion) + Nuevo.getx() * interpolacion;
//        return movimientox;
//    }
//
//    float InterpolacionRendery(Estado& Anterior, Estado& Nuevo, float interpolacion) {
//
//        float movimientoy = Anterior.gety()*(1 - interpolacion) + Nuevo.gety() * interpolacion;
//        return movimientoy;
//    }
     
}; 
#endif /* CSCREEN_HPP */

