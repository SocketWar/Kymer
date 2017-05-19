/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mapa1.hpp"
#include "sonido.h"

Mapa1::Mapa1(void) {
    update = 1000 / 25;
    frameskip = 5;

    anchura = 1024;
    altura = 720;

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
    int numeroenemigos = 1;
    int vacas = 4;
    objetos *machineGun;
    machineGun = new objetos('a');
    Jugador jugador(anchura, altura);
    Enemigo **enemigos = new Enemigo*[numeroenemigos];

    for (int i = 0; i < numeroenemigos; i++) {

        
            enemigos[i] = new Enemigo(4);
        
    }


    View vista(Vector2f(jugador.getPos().x, jugador.getPos().y), Vector2f(App.getSize().x, App.getSize().y));
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

    hud *h = new hud(vista);
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
            jugador.recogeObjeto(*machineGun);
            //enemigo
            for (int i = 0; i < numeroenemigos; i++) {

                enemigos[i]->calcularColision(map.getColisiones(), map.getnColisiones());
                enemigos[i]->ColisionJugador(jugador);
                enemigos[i]->update(tiempo,tiempoAnimacion ,jugador);
            }



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
                h->changeGranada(contg);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                contg--;
                h->changeGranada(contg);
            }
            if (Keyboard::isKeyPressed(Keyboard::Num0)) {
                h->changeTime(0);
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
                return 0;

            if (Keyboard::isKeyPressed(Keyboard::P))
                pausa = true;

            if (Keyboard::isKeyPressed(Keyboard::A)) {
                // sound.setVolume(1);
                //                disparo.getSonido().play();
                //sound2.play();
            }

            /*
            if (boxR.intersects(item->getHitbox())) {
                item->recogerObjeto();
                h->changePunt(item->getPuntos());
            }
             */
        }


        //interpolacion de movimiento
        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);




        //limpiampos pantalla
        App.clear(Color(150, 200, 200));

        //dibujamos 
        App.draw(map);
        jugador.render(interpolacion, tiempoAnimacion,*h);
        machineGun->RenderObjeto();

        for (int i = 0; i < numeroenemigos; i++) {

            enemigos[i]->render(interpolacion, tiempoAnimacion);

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


