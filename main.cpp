//#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "screens.hpp"
#include "cabecera.hpp"

int main(int argc, char** argv)
{
	//Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	//creacion de la pantalla
	sf::RenderWindow App(sf::VideoMode(1352, 888), "Kymer");

	//Mouse cursor no more visible
	App.setMouseCursorVisible(false);

	//Screens preparations
	menu s0;
	Screens.push_back(&s0);
	Mapa1 s1;
	Screens.push_back(&s1);
        //CARGA SONIDO
       


	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}