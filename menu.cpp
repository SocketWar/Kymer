/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "menu.hpp"

menu::menu(void) {
    alpha_max = 3 * 255; //atenuacion 3*255
    alpha_div = 3 ; // 3
    playing = false;
    options = false;
    versus = false;
    comoJugar = false;
}

int menu::Run() {
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& App= motor->getWindow();
    View vista(Vector2f(App.getSize().x / 2, App.getSize().y / 2), 
            Vector2f(App.getSize().x, App.getSize().y));
    
    App.setView(vista);
    Event Event;
    bool Running = true;
    
    Texture Texture;
    sf::Texture como;
    Sprite sprite;
    
    
    /*carga imagen howToPlay*/
    int alpha = alpha_max;
    
    Font Font;
    Text Menu1;
    Text Menu2;
    Text MenuOptions;
    Text MenuPVP;
    Text MenuComoJugar;
    Text Menu3;
    
    int menu = 0;

    if (!Texture.loadFromFile("res/img/menu.png")) {
        cerr << "Error loading menu.png" << std::endl;
        return (-1);
    }
       if (!como.loadFromFile("res/img/Controls.png")) {
        cerr << "Error loading menu.png" << std::endl;
        return (-1);
    }
    
    sprite.setTexture(Texture);
    sprite.setScale(motor->getEscala());
    sprite.setColor(sf::Color(255, 255, 255, alpha));
    if (!Font.loadFromFile("letras.ttf")) {
        std::cerr << "letras.ttf" << std::endl;
        return (-1);
    }
    
    float tamFuente = 90 * motor->getEscala().x;
    
     Menu1.setFont(Font);
    Menu1.setCharacterSize(tamFuente);
    Menu1.setString("Play");
    Menu1.setPosition(Vector2f(555.f * motor->getEscala().x, 300.f * motor->getEscala().y));

    MenuPVP.setFont(Font);
    MenuPVP.setCharacterSize(tamFuente);
    MenuPVP.setString("Versus");
    MenuPVP.setPosition(Vector2f(535.f * motor->getEscala().x, 400.f * motor->getEscala().y));

    MenuOptions.setFont(Font);
    MenuOptions.setCharacterSize(tamFuente);
    MenuOptions.setString("Options");
    MenuOptions.setPosition(Vector2f(520.f * motor->getEscala().x, 520.f * motor->getEscala().y));

    Menu2.setFont(Font);
    Menu2.setCharacterSize(tamFuente);
    Menu2.setString("Exit");
    Menu2.setPosition(Vector2f(575.f * motor->getEscala().x, 630.f * motor->getEscala().y));

    MenuComoJugar.setFont(Font);
    MenuComoJugar.setCharacterSize(tamFuente);
    MenuComoJugar.setString("How to play?");
    MenuComoJugar.setPosition(Vector2f(430.f * motor->getEscala().x, 750.f * motor->getEscala().y));

    Menu3.setFont(Font);
    Menu3.setCharacterSize(tamFuente);
    Menu3.setString("Continue");
    Menu3.setPosition(Vector2f(500.f * motor->getEscala().x, 300.f * motor->getEscala().y));

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
                        if (menu == 0){
                          menu = 4;  
                        }else if (menu == 1){
                          menu = 0;  
                        }else if (menu == 2){
                            menu = 1;
                        }else if (menu == 3){
                            menu = 2;
                        } else if (menu == 4){
                            menu = 3;
                        }
                        
                        break;
                    case Keyboard::Down:
                        if (menu == 0){
                          menu = 1;  
                        }else if (menu == 1){
                          menu = 2;  
                        }else if (menu == 2){
                            menu = 3;
                        }else if (menu == 3){
                            menu = 4;
                        }else if (menu == 4){
                            menu = 0;
                        }
                        
                        
                        break;
                    case Keyboard::Return:
                        if (menu == 0) {
                            //Let's get play !
                            playing = true;
                            options = false;
                            versus = false;
                            comoJugar = false;
                            return (1);
                        } else if (menu == 1){
                            playing = false;
                            options = false;
                            versus = true; 
                            comoJugar = false;
                        } else if (menu == 2){
                            playing = false;
                            options = true;
                            versus = false;
                            comoJugar = false;
                        } else if(menu==4 && comoJugar){
                            playing = false;
                            options = false;
                            versus = false;
                            comoJugar = false;
                            sprite.setTexture(Texture);
                            menu = 0;
                        } else if(menu==4){
                            playing = false;
                            options = false;
                            versus = false;
                            comoJugar = true;
                        }else{
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
        sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
        if (menu == 0) {
            Menu1.setColor(Color(255, 0, 0, 255));  
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
            Menu3.setColor(Color(255, 0, 0, 255));
        } else if (menu == 1){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 0, 0, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
            Menu3.setColor(Color(255, 255, 255, 255));
        } else if (menu == 2){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 0, 0, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
        } else if ( menu == 3){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 0, 0, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
        } else if ( menu == 4){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 0, 0, 255));
        }
        //Clearing screen
        App.clear();
        //Drawing
     if(comoJugar){
         
         sprite.setTexture(como);
//         if(sf::Keyboard::Key(Keyboard::Return)){
//             comoJugar== false;
//             sprite.setTexture(Texture);
//         }
     }
      
         App.draw(sprite);
        if (alpha == alpha_max) {
            if (playing) {
                App.draw(Menu3);
                MenuComoJugar.setPosition(Vector2f(400.f * motor->getEscala().x, 400.f * motor->getEscala().y));
            } else {
                if (!comoJugar) {
                    App.draw(Menu1);
                    App.draw(MenuPVP);
                    MenuComoJugar.setPosition(Vector2f(430.f * motor->getEscala().x, 750.f * motor->getEscala().y));
                }
            }
            if (!comoJugar) {
                App.draw(MenuOptions);
                App.draw(Menu2); //exit
                App.draw(MenuComoJugar);
            }
        }
        App.display();
    }

    //si da algun error, cierra 
    return (-1);
}