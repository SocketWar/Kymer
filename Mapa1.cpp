/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mapa1.hpp"
#include "sonido.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

Mapa1::Mapa1(string mapa, string tileSheet) {
    update = 1000 / 25;
    frameskip = 5;

    anchura = 1024;
    altura = 720;

    this->mapa = mapa;
    this->tileSheet = tileSheet;
}

int Mapa1::Run() {
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& App = motor->getWindow();
    bool Running = true; //booleano que controla el bucle mientras la pantalla esta seleccionada

    //App.setSize(Vector2u(App.getSize().x,App.getSize().y));
    Event event;
    //cout << "el mapa se muestra en  :" << anchura << "x" << altura << endl;
    App.setFramerateLimit(120);
    // ---------------------------------------
    // RELOJES Y TIEMPOS
    // ---------------------------------------
    Clock clock1;
    Clock clocl2;
    Time tiempo;
    Time tiempoAnimacion;


    //----------------------------------------
    // SONIDOS
    //----------------------------------------
    //    sonido disparo;
    //    disparo.setSonido("res/audio/shot.wav");

    SoundBuffer buffer;
    if (!buffer.loadFromFile("res/audio/menu.ogg")) {
        cout << " el archivo de audio Menu no esta disponible" << endl;
    }
    Sound sound;
    sound.setBuffer(buffer);

    sound.play();
    sound.setLoop(true);

    SoundBuffer bufferd;
    if (!bufferd.loadFromFile("res/audio/shot.wav")) {
        cout << " el archivo de audio Menu no esta disponible" << endl;
    }
    Sound sound2;
    sound2.setBuffer(bufferd);


    // ---------------------------------------
    // INTERPOLACION
    // ---------------------------------------
    Int32 tiempoupdate = clock1.getElapsedTime().asMilliseconds();
    int bucle = 0;
    float interpolacion;


    // ---------------------------------------
    // ELEMENTOS DE JUEGO
    // ---------------------------------------
    mapaTmx map(mapa, tileSheet);

    int numeroenemigos = 30;
    int contemigos = 0;
    int cont = 0;
    int nspawn = 0;
    objetos **machineGun = new objetos*[map.getnPuntos()];
    //Enemigo **enemigos = new Enemigo*[numeroenemigos];
    std::vector<Enemigo*> enemigos;

    for (int i = 0; i < map.getnPuntos(); i++) {
        Vector2f *v = map.getPuntuaciones()[i];
        machineGun[i] = new objetos('v', v->x, v->y);
    }

    Jugador jugador(anchura, altura, 1900, 50);




    View vista(Vector2f(jugador.getPos().x, jugador.getPos().y), Vector2f(App.getSize().x, App.getSize().y));
    vista.setCenter(Vector2f(App.getSize().x / 2, App.getSize().y / 2));


    // ---------------------------------------
    // HUD
    // ---------------------------------------

    Font *fuente = new Font();
    hud *h = new hud(vista);

    // ---------------------------------------
    // PAUSA
    // ---------------------------------------
    bool pausa = false;
    Text textoPausa;
    textoPausa.setFont(*fuente);
    textoPausa.setCharacterSize(100);
    textoPausa.setString("PAUSA");
    vista.zoom(1.05);
    while (Running) {

        bucle = 0;
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoAnimacion += tiempo;
            tiempoupdate += update;
            bucle++;
            //estados
            Event evento;
            while (App.pollEvent(evento)) {
                if (evento.type == Event::Closed)
                    App.close();
            }
            //llamadas a update
            //jugador

            jugador.calcularColision(map.getColisiones(), map.getnColisiones());
            jugador.update(tiempo);

            for (int i = 0; i < map.getnPuntos(); i++) {
                jugador.recogeObjeto(*machineGun[i]);

            }

            if (enemigos.size() < numeroenemigos) {

                for (int i = nspawn; i < map.getnSpawn(); i++) {
                    Vector2f *v = map.getSpawn()[i];
                    float posicion = v->x - jugador.getPos().x;

                    if (posicion <= 1000) {

                        for (int j = contemigos; j < numeroenemigos; j++) {
                            if (cont < 3) {
                                Enemigo *enemigo = new Enemigo(4, v->x, v->y);
                                enemigos.push_back(enemigo);
                                contemigos++;
                                cont++;
                            }
                            if (cont == 2) {
                                nspawn++;
                            }
                        }
                        cont = 0;
                    }
                }
            }
            cout << "numero enemigos---->>>" << contemigos << endl;

            //enemigo
            std::vector<Enemigo*> enemigosAux;
            for (int i = 0; i < enemigos.size(); i++) {
                if(enemigos[i]->getVidas()>0){
                    int posicion = abs(jugador.getPos().x - enemigos[i]->getPos().x);
                    if (posicion <= 1000) {
                        enemigos[i]->calcularColision(map.getColisiones(), map.getnColisiones());
                        enemigos[i]->ColisionJugador(jugador);
                        enemigos[i]->update(tiempo, tiempoAnimacion, jugador);
                    }
                    enemigosAux.push_back(enemigos[i]);
                }else{
                    
                    enemigos[i]->~Enemigo();
                    cout << "Muerto " << i << endl;
                }

            }
            enemigos=enemigosAux;



            //ELIMINADAS TECLAS HUD
            if (Keyboard::isKeyPressed(Keyboard::Num0)) {
                h->changeTime(0);
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape) || Joystick::isButtonPressed(0,7))
                return 0;

            if (Keyboard::isKeyPressed(Keyboard::P))
                pausa = true;

            if (Keyboard::isKeyPressed(Keyboard::A)) {
                // sound.setVolume(1);
                //                disparo.getSonido().play();
                //sound2.play();
            }
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                return 2;
            }
        }

        //interpolacion de movimiento
        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);




        //limpiampos pantalla
        App.clear(Color(150, 200, 200));

        //dibujamos 
        App.draw(map);
        jugador.render(interpolacion, tiempoAnimacion, *h);

        for (int i = 0; i < map.getnPuntos(); i++) {
            machineGun[i]->RenderObjeto();
        }


        for (int i = 0; i < enemigos.size(); i++) {
            if(enemigos[i]->getVidas()>0){
                int posicion = abs(jugador.getPos().x - enemigos[i]->getPos().x);
                if (posicion <= 1000)
                    enemigos[i]->render(interpolacion, tiempoAnimacion);
            }

        }

        vista.setCenter(Vector2f(jugador.getPos().x, vista.getCenter().y));
        App.setView(vista);
        //enemigo->RenderGranada(App);
        h->Update(vista);
        h->render();
        jugador.setVidas(h->getContHP());
        App.display();

    }

    //Never reaching this point normally, but just in case, exit the application
    return -1;
}


