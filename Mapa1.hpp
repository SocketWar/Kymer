/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa1.hpp
 * Author: darktom
 *
 * Created on May 7, 2017, 9:53 PM
 */

#ifndef MAPA1_HPP
#define MAPA1_HPP

#include <iostream>
#include "cScreen.hpp"
#include "cabecera.hpp"
#include "mapaTmx.h"
#include "MovimientoIA.h"
#include "Jugador.h"
#include "hud.h"
#include "ObjetoPuntuacion.h"
#include "Enemigo.h"
#include "Motor2D.h"

using namespace std;
using namespace sf;

class Mapa1 : public cScreen {
private:
    int update;
    int frameskip;
    int anchura;
    int altura;
public:
    Mapa1(void);
    virtual int Run();

};

#endif /* MAPA1_HPP */

