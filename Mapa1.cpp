/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mapa1.hpp"

Mapa1::Mapa1(void) {
    update = 1000 / 25;
    frameskip = 5;

    anchura = 1352;
    altura = 888;


}

int Mapa1::Run(RenderWindow &App) {

    bool Running = true; //booleano que controla el bucle mientras la pantalla esta seleccionada

    //App.setSize(Vector2u(App.getSize().x,App.getSize().y));
    Event event;
    cout << "el mapa se muestra en  :" << anchura << "x" << altura << endl;

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
    Vector2f movInterpolado;

    // ---------------------------------------
    // ELEMENTOS DE JUEGO
    // ---------------------------------------
    int desplazamientoCamara = 500;
    Jugador jugador(anchura, altura);
    Enemigo enemigo;
    cout<<"donde coño esta la puta vaca : "<<enemigo.getAnimacion().getSpriteE().getPosition().x<<","<<enemigo.getAnimacion().getSpriteE().getPosition().y
<<endl;
    View vista( Vector2f(jugador.getPos().x + desplazamientoCamara, jugador.getPos().y), Vector2f(App.getSize().x, App.getSize().y) );
    vista.setCenter(Vector2f(App.getSize().x / 2, App.getSize().y / 2));

    mapaTmx map;

    // ---------------------------------------
    // HUD
    // ---------------------------------------
   
    Font *fuente = new Font();
    /*Texture *cuadradoPuntuacion = new Texture();

    if (!cuadradoPuntuacion->loadFromFile("res/img/pru.png")) {
        cerr << "Error cargando la imagen pru.png";
        exit(0);
    }*/

    hud *h = new hud(vista,jugador);
    // ObjetoPuntuacion *item = new ObjetoPuntuacion(cuadradoPuntuacion, 900, 550, 128, 128, 2000);
    //Rect<float> boxR(300, 250, 50, 50);
  

    // ---------------------------------------
    // PAUSA
    // ---------------------------------------
    bool pausa = false;
    Text textoPausa;
    textoPausa.setFont(*fuente);
    textoPausa.setCharacterSize(100);
    textoPausa.setString("PAUSA");
    Vector2f centro(vista.getCenter().x - desplazamientoCamara, vista.getSize().y / 4);


    while (Running) {
        if(!pausa){
        bucle = 0;
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoAnimacion += tiempo;
            tiempoupdate += update;
            bucle++;
            //estados
            jugador.actualizarEstado(); //actualiza el estado del jugador(estado viejo = estado nuevo)
            Event evento;
            while (App.pollEvent(evento)) {
                if (evento.type == Event::Closed)
                    App.close();
            }
            //llamadas a update
            jugador.Movimiento(tiempo);
            enemigo.Movimiento(tiempo);
            jugador.Saltar();
            jugador.Disparar();
            jugador.UpdateDisparo();
            jugador.DispararGranada();
            jugador.Morir();

            //actualizar estados
            //  nuevo.actualizartiempo(jugador.getPos().x, jugador.getPos().y);
            jugador.setEstado(); //despues de moverse el jugador, cambia el estado nuevo en x e y actuales
            int lifePlayer = h->getContHP();
            int cont = h->getPunt();
            int contg = h->getContGranada();

            if (Keyboard::isKeyPressed(Keyboard::Add)) {
                lifePlayer = lifePlayer + 1;
                h->changeContHP(lifePlayer);

            }
            if (Keyboard::isKeyPressed(Keyboard::Subtract)) {
                lifePlayer = lifePlayer - 1;
                h->changeContHP(lifePlayer);
            }
            if (Keyboard::isKeyPressed(Keyboard::Multiply)) {
                cont = cont + 1;
                h->changePunt(cont);

            }
            if (Keyboard::isKeyPressed(Keyboard::Divide)) {
                cont = cont - 1;
                h->changePunt(cont);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num1)) {

                h->changeArma(0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)) {

                h->changeArma(1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                contg++;
                h->changeGranada(contg,jugador);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                contg--;
                h->changeGranada(contg,jugador);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num0)) {
                h->changeTime(0);
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                return 0;
            
            if (Keyboard::isKeyPressed(Keyboard::P))
                pausa = true;
            
            /*
            if (boxR.intersects(item->getHitbox())) {
                item->recogerObjeto();
                h->changePunt(item->getPuntos());
            }
             */
        }
        
        
        //interpolacion de movimiento
        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);

        movInterpolado = jugador.getViejo()->getInterpolacion(jugador.getViejo(), jugador.getNuevo(), interpolacion); //alamacena en un vector la interpolacion

        vista.setCenter(Vector2f(jugador.getPos().x + desplazamientoCamara, vista.getCenter().y));
        App.setView(vista);

        jugador.getAnimacion().MovimientoInterpolado(movInterpolado);

        //limpiampos pantalla
        App.clear(Color(150, 200, 200));

        //dibujamos 
        App.draw(map);
        App.draw(jugador.getAnimacion().getSprite(jugador.getActual(), jugador.getframeActual(tiempoAnimacion)));
        App.draw(enemigo.getAnimacion().getSprite(enemigo.getActual(), enemigo.getframeActual(tiempoAnimacion)));

        jugador.RenderDisparo(App);
        //cout << "VISTA => " << vista.getCenter().x <<  ", " << vista.getCenter().y << endl;
        if(h->Update(App, vista,jugador)){
            //pausa=true;
        }
        
        App.display();
        }
        else{
            centro.x = vista.getCenter().x;
            centro.y =  vista.getSize().y / 6;
            
            textoPausa.setPosition(centro);
            
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                return 0;
            
            if (Keyboard::isKeyPressed(Keyboard::O))
                pausa = false;
            
            
            App.draw(textoPausa);
            App.display();
        }
    }

    //Never reaching this point normally, but just in case, exit the application
    return -1;
}


