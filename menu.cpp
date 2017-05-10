/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "menu.hpp"

menu::menu(void) {
    alpha_max = 3 * 255; //atenuacion
    alpha_div = 3;
    playing = false;
}

int menu::Run(RenderWindow &App) {
    View vista(Vector2f(App.getSize().x / 2, App.getSize().y / 2), 
            Vector2f(App.getSize().x, App.getSize().y));
    
    App.setView(vista);
    Event Event;
    bool Running = true;
    
    Texture Texture;
    Sprite Sprite;
    
    int alpha = 0;
    
    Font Font;
    Text Menu1;
    Text Menu2;
    Text Menu3;
    
    int menu = 0;

    if (!Texture.loadFromFile("res/img/menu.png")) {
        cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    //cout<<"tam de menu:"<<   Texture.getSize().x <<","<<   Texture.getSize().y<<endl;
    Texture.getSize().x;
    Sprite.setTexture(Texture);
    Sprite.setColor(sf::Color(255, 255, 255, alpha));
    if (!Font.loadFromFile("letras.ttf")) {
        std::cerr << "letras.ttf" << std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(90);
    Menu1.setString("Play");
    Menu1.setPosition(Vector2f(550.f, 300.f));


    Menu2.setFont(Font);
    Menu2.setCharacterSize(90);
    Menu2.setString("Exit");
    Menu2.setPosition(Vector2f(550.f, 400.f));

    Menu3.setFont(Font);
    Menu3.setCharacterSize(90);
    Menu3.setString("Continue");
    Menu3.setPosition(Vector2f(550.f, 300.f));

    if (playing) {
        alpha = alpha_max;
    }
    //carga sonido menu
    SoundBuffer buffer;
    if (!buffer.loadFromFile("res/audio/menu.ogg")) {
        cout << " el archivo de audio Menu no esta disponible" << endl;
    }
    Sound sound;
    sound.setBuffer(buffer);

    sound.play();
    //carga sonido seleccion
    sf::SoundBuffer bufferSeleccion;
    if (!bufferSeleccion.loadFromFile("res/audio/MenuSeleccion.wav")) {
        cout << " el archivo de audio Menu no esta disponible" << endl;
    }
    Sound soundSeleccion;
    soundSeleccion.setBuffer(bufferSeleccion);
    soundSeleccion.stop();



    while (Running) {
        //Verifying events
        while (App.pollEvent(Event)) {
            // Window closed
            if (Event.type == Event::Closed) {
                return (-1);
            }
            //Key pressed
            if (Event.type == Event::KeyPressed) {
                soundSeleccion.play();
                switch (Event.key.code) {
                    case Keyboard::Up:
                        soundSeleccion.play();
                        menu = 0;
                        break;
                    case Keyboard::Down:
                        menu = 1;
                        break;
                    case Keyboard::Return:
                        if (menu == 0) {
                            //Let's get play !
                            playing = true;
                            return (1);
                        } else {
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
        if (alpha < alpha_max) {

            alpha++;
        }
        Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
        if (menu == 0) {
            Menu1.setColor(Color(255, 0, 0, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            Menu3.setColor(Color(255, 0, 0, 255));
        } else {
            Menu1.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 0, 0, 255));
            Menu3.setColor(Color(255, 255, 255, 255));
        }

        //Clearing screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        if (alpha == alpha_max) {
            if (playing) {
                App.draw(Menu3);
            } else {
                App.draw(Menu1);
            }
            App.draw(Menu2);
        }
        App.display();
    }

    //si da algun error, cierra 
    return (-1);
}