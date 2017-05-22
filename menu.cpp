/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "menu.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

menu::menu(void) {
    alpha_max = 3 * 255; //atenuacion 3*255
    alpha_div = 3 ; // 3
    playing = false;
    options = false;
    versus = false;
    comoJugar = false;
    spa = false;
    Sound = new sonido();
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
    sf::Texture opt;
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
    Text sonido;
    Text lang;
    
    float son = 50;
    
    int menu = 0;
    int menuOpt = 0;
    int menuPause = 0;

    if (!Texture.loadFromFile("res/img/menu.png")) {
        cerr << "Error loading menu.png" << std::endl;
        return (-1);
    }
    if (!como.loadFromFile("res/img/Controls.png")) {
        cerr << "Error loading controles.png" << std::endl;
        return (-1);
    }
    if (!opt.loadFromFile("res/img/Opt.png")) {
        cerr << "Error loading opciones.png" << std::endl;
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
    Menu3.setString("Restart");
    Menu3.setPosition(Vector2f(500.f * motor->getEscala().x, 300.f * motor->getEscala().y));
    
    sonido.setFont(Font);
    sonido.setCharacterSize(tamFuente);
    std::ostringstream osl;
    osl << "Volumen: - "<<son<<" +";
    sonido.setString(osl.str());
    sonido.setPosition(Vector2f(380.f * motor->getEscala().x, 180.f * motor->getEscala().y));
    
    lang.setFont(Font);
    lang.setCharacterSize(tamFuente);
    lang.setString("Language: English -");
    lang.setPosition(Vector2f(320.f * motor->getEscala().x, 300.f * motor->getEscala().y));

    if (playing) {
        alpha = alpha_max;
    }
    //carga sonido menu
    SoundBuffer buffer;
    if (!buffer.loadFromFile("res/audio/menu.ogg")) {
        cout << " el archivo de audio Menu no esta disponible" << endl;
    }
    //Sound sound;
    //sound.setBuffer(buffer);
    //sound.setVolume(son);
    
    Sound->setSonido("res/audio/menu.ogg");
    Sound->setVolumen(son);
    Sound->reproducir();
    

    //carga sonido seleccion
    sf::SoundBuffer bufferSeleccion;
    if (!bufferSeleccion.loadFromFile("res/audio/MenuSeleccion.wav")) {
        cout << " el archivo de audio Menu no esta disponible" << endl;
    }
    //Sound soundSeleccion;
    //soundSeleccion.setBuffer(bufferSeleccion);
    //soundSeleccion.stop();



    while (Running) {
        //Verifying events
        while (App.pollEvent(Event)) {
            // Window closed
            if (Event.type == Event::Closed) {
                return (-1);
            }
            //Key pressed
            if (Event.type == Event::KeyPressed) {
                //soundSeleccion.play();
                switch (Event.key.code) {
                    case Keyboard::Up:
                        //soundSeleccion.play();
                       
                        if (menu == 0){
                          menu = 4;  
                        }else if (menu == 1){
                          menu = 0;  
                        }else if (menu == 2 && options){
                            if (menuOpt == 1)
                                menuOpt = 0;
                            else
                                menuOpt = 1;     
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
                            if (playing)
                                menu = 2;
                            else
                                menu = 1;  
                        }else if (menu == 1){
                          menu = 2;  
                        }else if (menu == 2 && options){
                            if (menuOpt == 1)
                                menuOpt = 0;
                            else
                                menuOpt = 1;     
                        }else if (menu == 2){
                            menu = 3;
                        }else if (menu == 3){
                            menu = 4;
                        }else if (menu == 4){
                            menu = 0;
                        }
                        
                        
                        
                        break;
                        
                    case Keyboard::Left:
                        if (menu==2){
                            if (menuOpt == 0){
                            if (son>0)
                            son = son-1;
                            if (son == 0){
                                sonido.setFont(Font);
                                sonido.setCharacterSize(tamFuente);
                                std::ostringstream osl;
                                osl << "Volumen:   "<<son<<" +";
                                sonido.setString(osl.str());
                                sonido.setPosition(Vector2f(380.f * motor->getEscala().x, 180.f * motor->getEscala().y));
                                Sound->setVolumen(son);
                            }else{
                                sonido.setFont(Font);
                                sonido.setCharacterSize(tamFuente);
                                std::ostringstream osl;
                                osl << "Volumen: - "<<son<<" +";
                                sonido.setString(osl.str());
                                sonido.setPosition(Vector2f(380.f * motor->getEscala().x, 180.f * motor->getEscala().y));
                                Sound->setVolumen(son);
                            }
                            }else if(menuOpt == 1){
                                spa = false;
                                lang.setFont(Font);
                                lang.setCharacterSize(tamFuente);
                                lang.setString("Language: English -");
                                lang.setPosition(Vector2f(320.f * motor->getEscala().x, 300.f * motor->getEscala().y));
                                //JUgar
                            Menu1.setFont(Font);
                            Menu1.setCharacterSize(tamFuente);
                            Menu1.setString("Play");
                            Menu1.setPosition(Vector2f(555.f * motor->getEscala().x, 275.f * motor->getEscala().y));
                            //Versus
                            MenuPVP.setFont(Font);
                            MenuPVP.setCharacterSize(tamFuente);
                            MenuPVP.setString("Versus");
                            MenuPVP.setPosition(Vector2f(535.f * motor->getEscala().x, 400.f * motor->getEscala().y));
                            //Opciones
                            MenuOptions.setFont(Font);
                            MenuOptions.setCharacterSize(tamFuente);
                            MenuOptions.setString("Options");
                            MenuOptions.setPosition(Vector2f(500.f * motor->getEscala().x, 500.f * motor->getEscala().y));
                            //Salir
                            Menu2.setFont(Font);
                            Menu2.setCharacterSize(tamFuente);
                            Menu2.setString("Exit");
                            Menu2.setPosition(Vector2f(575.f * motor->getEscala().x, 620.f * motor->getEscala().y));
                            //ComoJugar
                            MenuComoJugar.setFont(Font);
                            MenuComoJugar.setCharacterSize(tamFuente);
                            MenuComoJugar.setString("How to play?");
                            MenuComoJugar.setPosition(Vector2f(430.f * motor->getEscala().x, 720.f * motor->getEscala().y));
                            //Fondos
                            if (!como.loadFromFile("res/img/Controls.png")) {
                                cerr << "Error loading controles.png" << std::endl;
                                return (-1);
                            }
                            if (!opt.loadFromFile("res/img/Opt.png")) {
                                cerr << "Error loading opciones.png" << std::endl;
                                return (-1);
                            }
                            }
                        }
                        if (comoJugar){
                        if (!como.loadFromFile("res/img/Controls.png")) {
                            cerr << "Error loading controles.png" << std::endl;
                            return (-1);
                        }
                        if (spa == true){
                            if (!como.loadFromFile("res/img/ControlsSpa.png")) {
                            cerr << "Error loading controles.png" << std::endl;
                            return (-1);
                        }
                        }
                    }
                        break;
                        
                    case Keyboard::Right:
                    if (menu==2){
                        if (menuOpt == 0){
                        if (son<100)
                        son = son+1;
                        if (son == 100){
                            sonido.setFont(Font);
                            sonido.setCharacterSize(tamFuente);
                            std::ostringstream osl;
                            osl << "Volumen: - "<<son<<"  ";
                            sonido.setString(osl.str());
                            sonido.setPosition(Vector2f(380.f * motor->getEscala().x, 180.f * motor->getEscala().y));
                            Sound->setVolumen(son);
                        }else{
                            sonido.setFont(Font);
                            sonido.setCharacterSize(tamFuente);
                            std::ostringstream osl;
                            osl << "Volumen: - "<<son<<" +";
                            sonido.setString(osl.str());
                            sonido.setPosition(Vector2f(380.f * motor->getEscala().x, 180.f * motor->getEscala().y));
                            Sound->setVolumen(son); 
                        }
                        }else if(menuOpt == 1){
                            spa = true;
                            //Lenguaje
                            lang.setFont(Font);
                            lang.setCharacterSize(tamFuente);
                            lang.setString("Lenguaje: - Castellano");
                            lang.setPosition(Vector2f(250.f * motor->getEscala().x, 300.f * motor->getEscala().y));
                            //JUgar
                            Menu1.setFont(Font);
                            Menu1.setCharacterSize(tamFuente);
                            Menu1.setString("Jugar");
                            Menu1.setPosition(Vector2f(555.f * motor->getEscala().x, 275.f * motor->getEscala().y));
                            //Versus
                            MenuPVP.setFont(Font);
                            MenuPVP.setCharacterSize(tamFuente);
                            MenuPVP.setString("Versus");
                            MenuPVP.setPosition(Vector2f(535.f * motor->getEscala().x, 400.f * motor->getEscala().y));
                            //Opciones
                            MenuOptions.setFont(Font);
                            MenuOptions.setCharacterSize(tamFuente);
                            MenuOptions.setString("Opciones");
                            MenuOptions.setPosition(Vector2f(500.f * motor->getEscala().x, 500.f * motor->getEscala().y));
                            //Salir
                            Menu2.setFont(Font);
                            Menu2.setCharacterSize(tamFuente);
                            Menu2.setString("Salir");
                            Menu2.setPosition(Vector2f(575.f * motor->getEscala().x, 620.f * motor->getEscala().y));
                            //ComoJugar
                            MenuComoJugar.setFont(Font);
                            MenuComoJugar.setCharacterSize(tamFuente);
                            MenuComoJugar.setString("Como jugar?");
                            MenuComoJugar.setPosition(Vector2f(430.f * motor->getEscala().x, 720.f * motor->getEscala().y));
                            //Fondos
                            if (!como.loadFromFile("res/img/ControlsSpa.png")) {
                                cerr << "Error loading controles.png" << std::endl;
                                return (-1);
                            }
                            if (!opt.loadFromFile("res/img/OptSpa.png")) {
                                cerr << "Error loading opciones.png" << std::endl;
                                return (-1);
                            }
                            
                        }
                        
                    }
                    
                    if (comoJugar){
                        if (!como.loadFromFile("res/img/ControlsXbox.png")) {
                            cerr << "Error loading controles.png" << std::endl;
                            return (-1);
                        }
                        if (spa == true){
                            if (!como.loadFromFile("res/img/ControlsXboxSpa.png")) {
                            cerr << "Error loading controles.png" << std::endl;
                            return (-1);
                        }
                        }
                    }

                    break;
                    case Keyboard::Return:
                        if (menu == 0) {
                            //Let's get play !
                            playing = true;
                            options = false;
                            versus = false;
                            comoJugar = false;
                            Sound->detener();
                            return (1);
                        } else if (menu == 1){
                            playing = false;
                            options = false;
                            versus = true; 
                            comoJugar = false;
                        } else if (menu == 2 && options){
                            playing = false;
                            options = false;
                            versus = false;
                            comoJugar = false;
                            sprite.setTexture(Texture);
                            menu == 0;
                        }else if (menu == 2){
                            playing = false;
                            options = true;
                            versus = false;
                            comoJugar = false;
                        } else if(menu==4 && comoJugar){
                            sprite.setTexture(Texture);
                            menu = 0;
                            options = false;
                            versus = false;
                            comoJugar = false;
                            
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
            sonido.setColor(Color(255, 255, 255, 255));
        } else if (menu == 1){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 0, 0, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
            Menu3.setColor(Color(255, 255, 255, 255));
            sonido.setColor(Color(255, 255, 255, 255));
        } else if (menu == 2){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 0, 0, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
            Menu3.setColor(Color(255, 255, 255, 255));
            sonido.setColor(Color(255, 255, 255, 255));
            lang.setColor(Color(255, 255, 255, 255));
        } else if ( menu == 3){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 0, 0, 255));
            Menu3.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 255, 255, 255));
            sonido.setColor(Color(255, 255, 255, 255));
        } else if ( menu == 4){
            Menu1.setColor(Color(255, 255, 255, 255));
            MenuPVP.setColor(Color(255, 255, 255, 255));
            MenuOptions.setColor(Color(255, 255, 255, 255));
            Menu2.setColor(Color(255, 255, 255, 255));
            Menu3.setColor(Color(255, 255, 255, 255));
            MenuComoJugar.setColor(Color(255, 0, 0, 255));
            sonido.setColor(Color(255, 255, 255, 255));
        }
        
        if (menuOpt == 0){
            sonido.setColor(Color(255, 0, 0, 255));
            lang.setColor(Color(255, 255, 255, 255));
        } else if (menuOpt == 1){
            sonido.setColor(Color(255, 255, 255, 255));
            lang.setColor(Color(255, 0, 0, 255));
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
                Menu3.setPosition(Vector2f(520.f * motor->getEscala().x, 300.f * motor->getEscala().y));
                MenuComoJugar.setPosition(Vector2f(430.f * motor->getEscala().x, 750.f * motor->getEscala().y));
                Menu2.setPosition(Vector2f(580.f * motor->getEscala().x, 520.f * motor->getEscala().y));
                MenuOptions.setPosition(Vector2f(535.f * motor->getEscala().x, 400.f * motor->getEscala().y));
            } else {
                if (!comoJugar && !options) {
                    App.draw(Menu1);
                    App.draw(MenuPVP);
                    MenuComoJugar.setPosition(Vector2f(430.f * motor->getEscala().x, 750.f * motor->getEscala().y));
                    Menu2.setPosition(Vector2f(575.f * motor->getEscala().x, 630.f * motor->getEscala().y));
                    MenuOptions.setPosition(Vector2f(520.f * motor->getEscala().x, 520.f * motor->getEscala().y));
                }
            }
            if (!comoJugar && !options) {
                App.draw(MenuOptions);
                App.draw(Menu2); //exit
                App.draw(MenuComoJugar);
            }
        }
         
        if (options){
            sprite.setTexture(opt);
            App.draw(sonido);
            App.draw(lang);
        }
        App.display();
    }

    //si da algun error, cierra 
    return (-1);
}