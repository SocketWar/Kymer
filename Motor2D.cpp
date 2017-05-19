/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motor2D.cpp
 * Author: pepas
 * 
 * Created on 13 de mayo de 2017, 1:13
 */

#include "Motor2D.h"


Motor2D* Motor2D::instancia;
bool Motor2D::inst = false;
//creamos la ventana en el contructor nada mas crear la instancia

Motor2D::Motor2D() {
    window = new RenderWindow(VideoMode(1280, 720), "Kymer", Style::Close);
    
    //REFERENCIA AL TAMAÑO DE LA IMAGEN DEL MENU
    escala.x = (float) window->getSize().x/ 1366;
    escala.y = (float) window->getSize().y / 888;
    
    inst = true;
}
//comprobamos si existe y si no se crea una nueva

Motor2D* Motor2D::GetInstance() {
    if (!inst) {
        instancia = new Motor2D();
    }
    return instancia;
}

//en caso de eliminar la instancia la variable de control sera false
Motor2D::~Motor2D() {
    inst = false;
}

RenderWindow& Motor2D::getWindow() {
    return *window;
}

Vector2f Motor2D::getEscala(){
    return escala;
}

