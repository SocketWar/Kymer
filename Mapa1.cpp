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

    anchura = 1352;
    altura = 888;


}

int Mapa1::Run() {
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& App= motor->getWindow();
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
    int desplazamientoCamara = 500;
    Jugador jugador(anchura, altura);
    Enemigo *enemigo;
    Enemigo *enemigo2;
    Enemigo *enemigo3;
    Enemigo *enemigo4;
    Enemigo *enemigo5;
    Enemigo *enemigo6;
    
    enemigo = new Enemigo(4);
    enemigo3 = new Enemigo(4);
    enemigo4 = new Enemigo(4);
    enemigo5 = new Enemigo(4);
    enemigo6 = new Enemigo(4);
    enemigo2=new Enemigo(1);
  
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
            Event evento;
            while (App.pollEvent(evento)) {
                if (evento.type == Event::Closed)
                    App.close();
            }
            //llamadas a update
            //jugador
            jugador.calcularColision(map.getColisiones(),map.getnObjetos());
            jugador.update(tiempo);
            
            //enemigo
            enemigo->calcularColision(map.getColisiones(),map.getnObjetos());
            enemigo->update(tiempo,jugador);
            enemigo2->calcularColision(map.getColisiones(),map.getnObjetos());
            enemigo2->update(tiempo,jugador);
            enemigo3->calcularColision(map.getColisiones(),map.getnObjetos());
            enemigo3->update(tiempo,jugador);
            enemigo4->calcularColision(map.getColisiones(),map.getnObjetos());
            enemigo4->update(tiempo,jugador);
            enemigo5->calcularColision(map.getColisiones(),map.getnObjetos());
            enemigo5->update(tiempo,jugador);
            enemigo6->calcularColision(map.getColisiones(),map.getnObjetos());
            enemigo6->update(tiempo,jugador);
            
            
            

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
             
            if (Keyboard::isKeyPressed(Keyboard::A)){
               // sound.setVolume(1);
//                disparo.getSonido().play();
                sound2.play();
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

        vista.setCenter(Vector2f(jugador.getPos().x + desplazamientoCamara, vista.getCenter().y));
        App.setView(vista);

       
        //limpiampos pantalla
        App.clear(Color(150, 200, 200));

        //dibujamos 
        App.draw(map);
        jugador.render(interpolacion,tiempoAnimacion);
        enemigo->render(interpolacion,tiempoAnimacion);
        enemigo2->render(interpolacion,tiempoAnimacion);
        enemigo3->render(interpolacion,tiempoAnimacion);
        enemigo4->render(interpolacion,tiempoAnimacion);
        enemigo5->render(interpolacion,tiempoAnimacion);
        enemigo6->render(interpolacion,tiempoAnimacion);
        //enemigo->RenderGranada(App);
        //cout << "VISTA => " << vista.getCenter().x <<  ", " << vista.getCenter().y << endl;
        h->Update(App, vista,jugador);
        jugador.setVidas(h->getContHP());
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


