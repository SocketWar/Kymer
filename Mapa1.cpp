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

    int numeroenemigos = 80;
    int contemigos = 0;
    int cont = 0;
    int nspawn = 0;
    int objetoRandom = 0;

    objetos **machineGun = new objetos*[map.getnPuntos()];
    //Enemigo **enemigos = new Enemigo*[numeroenemigos];
    std::vector<Enemigo*> enemigos;

    for (int i = 0; i < map.getnPuntos(); i++) {
        objetoRandom = rand() % 3;
        Vector2f *v = map.getPuntuaciones()[i];
        machineGun[i] = new objetos(objetoRandom, v->x, v->y);
    }

    Jugador *jugador = new Jugador(anchura, altura, 1900, 50);




    View vista(Vector2f(jugador->getPos().x, jugador->getPos().y), Vector2f(App.getSize().x, App.getSize().y));
    vista.setCenter(Vector2f(App.getSize().x / 2, App.getSize().y / 1.45));


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

            jugador->calcularColision(map.getColisiones(), map.getnColisiones(), map.getMuerte());
            jugador->update(tiempo);

            for (int i = 0; i < map.getnPuntos(); i++) {
                jugador->recogeObjeto(*machineGun[i]);

            }

            if (enemigos.size() < numeroenemigos) {

                for (int i = nspawn; i < map.getnSpawn(); i++) {
                    Vector2f *v = map.getSpawn()[i];
                    float posicion = v->x - jugador->getPos().x;
                    int randomEnemy = 0;
                    if (posicion <= 1000) {

                        for (int j = contemigos; j < numeroenemigos; j++) {
                            if (cont < 6) {
                                randomEnemy = rand() % 5;
                                Enemigo *enemigo = new Enemigo(randomEnemy, v->x, v->y);
                                enemigos.push_back(enemigo);
                                contemigos++;
                                cont++;
                            }
                            if (cont == 5) {
                                nspawn++;
                            }
                        }
                        cont = 0;
                    }
                }
            }
            //cout << "numero enemigos---->>>" << contemigos << endl;

            //enemigo
            std::vector<Enemigo*> enemigosAux;
            for (int i = 0; i < enemigos.size(); i++) {
                if (enemigos[i]->getVidas() > 0) {
                    int posicion = abs(jugador->getPos().x - enemigos[i]->getPos().x);
                    if (posicion <= 1000) {
                        enemigos[i]->calcularColision(map.getColisiones(), map.getnColisiones(), map.getMuerte());
                        enemigos[i]->ColisionJugador(*jugador);
                        enemigos[i]->update(tiempo, tiempoAnimacion, *jugador);
                    }
                    enemigosAux.push_back(enemigos[i]);
                }else 
                    if(enemigos[i]->getVidas()<=0){
                        if(enemigos[i]->getTipo() == 1 || enemigos[i]->getTipo()==2){
                          cout<<"entro"<<endl;
                           
                           if (enemigos[i]->getMuerto()==true){
                             enemigos[i]->~Enemigo();
                               
                           }
                           else{
                                enemigosAux.push_back(enemigos[i]);

                           }
                    }
                }

            }
             enemigos=enemigosAux;

            if (jugador->gethitBox().getGlobalBounds().intersects(map.getFin())) {

                for(int i=0;i<enemigos.size();i++){
                    enemigos[i]->~Enemigo();
                }
                return 2;
            }
            //ELIMINADAS TECLAS HUD
            if (Keyboard::isKeyPressed(Keyboard::Num0)) {
                h->changeTime(0);
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape) || Joystick::isButtonPressed(0, 7))
                return 0;


            if (Keyboard::isKeyPressed(Keyboard::B)) {
                return 2;
                //cambio de mapa
            }
        }

        //interpolacion de movimiento
        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);




        //limpiampos pantalla
        App.clear(Color(150, 200, 200));

        //dibujamos 
        App.draw(map);
        jugador->render(interpolacion, tiempoAnimacion, *h);

        for (int i = 0; i < map.getnPuntos(); i++) {
            machineGun[i]->RenderObjeto();
        }


        for (int i = 0; i < enemigos.size(); i++) {
         // if(enemigos[i]->getVidas()>0){
          if(enemigos[i]->getMuerto() == false){
              int posicion = abs(jugador->getPos().x - enemigos[i]->getPos().x);
               if (posicion <= 1000)
                    enemigos[i]->render(interpolacion, tiempoAnimacion);
           }

        //}
        }
        vista.setCenter(Vector2f(jugador->getPos().x, vista.getCenter().y));
        App.setView(vista);
        //enemigo->RenderGranada(App);
        h->Update(vista);
        h->render();
        jugador->setVidas(h->getContHP());
        App.display();

    }

    //Never reaching this point normally, but just in case, exit the application
    return -1;
}


