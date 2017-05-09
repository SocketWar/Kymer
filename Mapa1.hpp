/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa1.hpp
 * Author: darktom
 *
 * Created on May 7, 2017, 9:53 PM
 */

#ifndef MAPA1_HPP
#define MAPA1_HPP

#include <iostream>
#include "cScreen.hpp"
#include "cabecera.hpp"
#include "mapaTmx.h"
#include "MovimientoIA.h"
#include "Jugador.h"
#include "hud.h"
#include "ObjetoPuntuacion.h"
#include "Enemigo.h"

using namespace std;
using namespace sf;

class Mapa1 : public cScreen
{
private:
    int update;
    int frameskip;
    int anchura;
    int altura;
public:
	Mapa1(void);
	virtual int Run(sf::RenderWindow &App);
//        virtual float InterpolacionRenderx(Estado& Anterior, Estado& Nuevo, float interpolacion); 
//        virtual float InterpolacionRendery(Estado& Anterior, Estado& Nuevo, float interpolacion);
};

Mapa1::Mapa1(void)

{      
        update = 1000 / 25;
        frameskip = 5;
	anchura = 800;
        altura = 600;
	
}


int Mapa1::Run(sf::RenderWindow &App)
{
	sf::Event event;
	bool Running = true;
        
    App.setFramerateLimit(120);
    // ---------------------------------------
    // RELOJES Y TIEMPOS
    // ---------------------------------------
    Clock clock1;
    Clock clocl2;
    Time tiempo;
    Time tiempoAnimacion;


    // ---------------------------------------
    // INTERPOLACION
    // ---------------------------------------
    Int32 tiempoupdate = clock1.getElapsedTime().asMilliseconds();
    int bucle = 0;
    float interpolacion;
    float movinterpoladox = 0;
    float movinterpoladoy = 0;

    // ---------------------------------------
    // ELEMENTOS DE JUEGO
    // ---------------------------------------
    
    Jugador jugador(anchura, altura);
    Enemigo enemigo;
    Estado nuevo(jugador.getPos().x, jugador.getPos().y);
    Estado viejo(0, 0);
    View vista(jugador.getPos(), Vector2f(anchura, altura));

    mapaTmx map;

    // ---------------------------------------
    // HUD
    // ---------------------------------------
    Texture *texHUD = new Texture();
    Texture *cuadradoPuntuacion = new Texture();
    Font *fuente = new Font();

    if (!texHUD->loadFromFile("res/img/hud.png")) {
        std::cerr << "Error cargando la imagen hud.png";
        exit(0);
    }

    if (!cuadradoPuntuacion->loadFromFile("res/img/pru.png")) {
        std::cerr << "Error cargando la imagen pru.png";
        exit(0);
    }


    if (!fuente->loadFromFile("res/font/Sansation_Regular.ttf")) {
        std::cerr << "Error cargando la fuente sansation.ttf";
        exit(0);
    }

    hud *h = new hud(texHUD, fuente, vista);
    ObjetoPuntuacion *item = new ObjetoPuntuacion(cuadradoPuntuacion, 900, 550, 128, 128, 2000);

    
    Rect<float> boxR(300, 250, 50, 50);
   
    vista.zoom(2);
    h->setarmas();
    h->setplayerHP();
	while (Running)
	{        bucle = 0;
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoAnimacion += tiempo;
            tiempoupdate += update;
            bucle++;
            //estados
            viejo = nuevo;
            Event evento;
            while (App.pollEvent(evento)) {
                if (evento.type == Event::Closed)
                    App.close();
            }
            //llamadas a update
            jugador.Movimiento(tiempo);
            jugador.Saltar();
            jugador.Disparar();
            jugador.UpdateDisparo();
            jugador.DispararGranada();

            //actualizar estados
            nuevo.actualizartiempo(jugador.getPos().x, jugador.getPos().y);

            int lifePlayer = h->getContHP();
            int cont = h->getPunt();
            int contg = h->getContGranada();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                lifePlayer = lifePlayer + 1;
                h->changeContHP(lifePlayer);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                lifePlayer = lifePlayer - 1;
                h->changeContHP(lifePlayer);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)) {
                cont = cont + 1;
                h->changePunt(cont);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)) {
                cont = cont - 1;
                h->changePunt(cont);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {

                h->changeArma(0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {

                h->changeArma(1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                contg++;
                h->changeGranada(contg);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                contg--;
                h->changeGranada(contg);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {

                h->changeTime(0);
            }

            if (boxR.intersects(item->getHitbox())) {
                item->recogerObjeto();
                h->changePunt(item->getPuntos());
            }
        }
        h->updateTime();
        //interpolacion de movimiento
        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);
//        movinterpoladox = InterpolacionRenderx(viejo, nuevo, interpolacion);
//        movinterpoladoy = InterpolacionRendery(viejo, nuevo, interpolacion);

        
        
        vista.setCenter(Vector2f(jugador.getPos().x, vista.getCenter().y));
        App.setView(vista);

        jugador.getAnimacion().MovimientoInterpolado(Vector2f(movinterpoladox, movinterpoladoy));

        //limpiampos pantalla
        App.clear(Color(150, 200, 200));
        
        //dibujamos 
        App.draw(map);
        App.draw(jugador.getAnimacion().getSprite(jugador.getActual(), jugador.getframeActual(tiempoAnimacion)));
        App.draw(enemigo.getAnimacion().getSprite(0,0));
        
        jugador.RenderDisparo(App);
        for (int n = 0; n < h->getContHP(); n++) {
            App.draw(h->getPlayerHP(n));
        }
        if (item->getRecogido() == false)
            App.draw(item->getSprite());

        //Window.draw(rectangulo);
        App.draw(h->getTextVida());
        App.draw(h->getArma());
        App.draw(h->getGranada());
        App.draw(h->getTextArma());
        App.draw(h->getIcono());
        App.draw(h->getTextPunt());
        App.draw(h->getTextTime());
        App.draw(h->getTextGranada());
        App.display();
		
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}



#endif /* MAPA1_HPP */

