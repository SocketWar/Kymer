//#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"
#include "cabecera.hpp"
#include "Motor2D.h"

int main(int argc, char** argv) {
    //Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;

    //creacion de la pantalla
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& App= motor->getWindow();

    //Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    //preparacion pantallas
    menu s0;//menu
    Screens.push_back(&s0);
    Mapa1 s1("res/tmx/mapa2Final.tmx", "res/img/tiles.png");//mapa1
    Screens.push_back(&s1);
    Mapa1 s2("res/tmx/mapa3Final.tmx", "res/img/tiles_2.png");//mapa2
    Screens.push_back(&s2);

    //Main loop
    while (screen >= 0) {
        screen = Screens[screen]->Run();
    }

    return EXIT_SUCCESS;
}