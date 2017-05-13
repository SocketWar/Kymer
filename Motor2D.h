/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor2D.h
 * Author: pepas
 *
 * Created on 13 de mayo de 2017, 1:13
 */

#ifndef MOTOR2D_H
#define MOTOR2D_H

#include "cabecera.hpp"
#include <iostream>

class Motor2D {
public:
    static Motor2D* GetInstance();
    virtual ~Motor2D();
    Motor2D();
    RenderWindow& getWindow();
private:
    static Motor2D *instancia;
    RenderWindow* window;
    static bool inst;
    
};

#endif /* MOTOR2D_H */

