/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   screen_0.hpp
 * Author: darktom
 *
 * Created on May 7, 2017, 3:23 PM
 */

#ifndef SCREEN_0_HPP
#define SCREEN_0_HPP

#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class screen_0 : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
       
public:
	screen_0(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_0::screen_0(void)
{
	alpha_max = 3 * 255;//atenuacion
	alpha_div = 3;
	playing = false;
}

int screen_0::Run(sf::RenderWindow &App)
{      
     View vista(Vector2f(App.getSize().x/2,App.getSize().y/2),
           Vector2f(App.getSize().x,App.getSize().y)
          );
     App.setView(vista);
	sf::Event Event;
	bool Running = true;
	sf::Texture Texture;
	sf::Sprite Sprite;
	int alpha = 0;
	sf::Font Font;
	sf::Text Menu1;
	sf::Text Menu2;
	sf::Text Menu3;
	int menu = 0;

	if (!Texture.loadFromFile("res/img/menu.png"))
	{
		std::cerr << "Error loading presentation.gif" << std::endl;
		return (-1);
	}
        //cout<<"tam de menu:"<<   Texture.getSize().x <<","<<   Texture.getSize().y<<endl;
        Texture.getSize().x;
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, alpha));
	if (!Font.loadFromFile("letras.ttf"))
	{
		std::cerr << "letras.ttf" << std::endl;
		return (-1);
	}
	Menu1.setFont(Font);
	Menu1.setCharacterSize(90);
	Menu1.setString("Play");
	Menu1.setPosition(Vector2f( 550.f, 300.f ));
      
        
	Menu2.setFont(Font);
	Menu2.setCharacterSize(90);
	Menu2.setString("Exit");
	Menu2.setPosition(Vector2f( 550.f, 400.f ));

	Menu3.setFont(Font);
	Menu3.setCharacterSize(90);
	Menu3.setString("Continue");
	Menu3.setPosition(Vector2f( 550.f, 300.f));

	if (playing)
	{
		alpha = alpha_max;
	}
        //carga sonido menu
        sf::SoundBuffer buffer;
         if (!buffer.loadFromFile("res/audio/menu.ogg")){
             cout<<" el archivo de audio Menu no esta disponible"<<endl;
         }
        sf::Sound sound;
        sound.setBuffer(buffer);
       
        sound.play();
        //carga sonido seleccion
        sf::SoundBuffer bufferSeleccion;
         if (!bufferSeleccion.loadFromFile("res/audio/MenuSeleccion.wav")){
             cout<<" el archivo de audio Menu no esta disponible"<<endl;
         }
        sf::Sound soundSeleccion;
        soundSeleccion.setBuffer(bufferSeleccion);
        soundSeleccion.stop();
  


	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
                            soundSeleccion.play();
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
                                    soundSeleccion.play();
					menu = 0;
					break;
				case sf::Keyboard::Down:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0)
					{
						//Let's get play !
						playing = true;
						return (1);
					}
					else
					{
						//Let's get work...
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
        
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
		if (menu == 0)
		{
			Menu1.setColor(sf::Color(255, 0, 0, 255));
			Menu2.setColor(sf::Color(255, 255, 255, 255));
			Menu3.setColor(sf::Color(255, 0, 0, 255));
		}
		else
		{
			Menu1.setColor(sf::Color(255, 255, 255, 255));
			Menu2.setColor(sf::Color(255, 0, 0, 255));
			Menu3.setColor(sf::Color(255, 255, 255, 255));
		}

		//Clearing screen
		App.clear();
		//Drawing
		App.draw(Sprite);
		if (alpha == alpha_max)
		{
			if (playing)
			{
				App.draw(Menu3);
			}
			else
			{
				App.draw(Menu1);
			}
			App.draw(Menu2);
		}
		App.display();
	}

	//si da algun error, cierra 
	return (-1);
}

#endif /* SCREEN_0_HPP */

