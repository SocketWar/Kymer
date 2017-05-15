#include "cabecera.hpp"
#include "mapaTmx.h"
#include "Estado.h"
#include "MovimientoIA.h"
#include "Jugador.h"
#include "hud.h"
#include "ObjetoPuntuacion.h"
#include "Enemigo.h"
#include "Motor2D.h"

const int update = 1000 / 25;
const int frameskip = 5;
int anchura = 1270;
int altura = 720;



int main() {
    
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& Window= motor->getWindow();
   //RenderWindow Window(VideoMode(anchura, altura), "Kymer");
   //cout<<motor->getchar()<<endl;

    Window.setFramerateLimit(120);
    
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

    // ---------------------------------------
    // ELEMENTOS DE JUEGO
    // ---------------------------------------
    Jugador jugador(anchura, altura);
    //jugador.getAnimacion().MovimientoInterpolado(Vector2f(1,1));
    Enemigo *enemigo;
    int tipoE=3;
    enemigo = new Enemigo(tipoE);
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

    hud *h = new hud(vista);
    /*
    ObjetoPuntuacion *item = new ObjetoPuntuacion(cuadradoPuntuacion, 900, 550, 128, 128, 2000);

    
    Rect<float> boxR(300, 250, 50, 50);
   
    vista.zoom(2);
    
*/
    
    
    h->setarmas();
    h->setplayerHP();
    
        
    while (Window.isOpen()) {   
                  
        bucle = 0;
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoAnimacion += tiempo;
            tiempoupdate += update;
            bucle++;
            
           
            Event evento;
            while (Window.pollEvent(evento)) {
                if (evento.type == Event::Closed)
                    Window.close();
            }
            //llamadas a update
            //jugador
            jugador.calcularColision(map.getColisiones(),map.getnObjetos());
            jugador.update(tiempo);
            enemigo->UpdateGranada();
            //enemigo
            enemigo->Movimiento(tiempo,jugador);
            
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
/*
            if (boxR.intersects(item->getHitbox())) {
                item->recogerObjeto();
                h->changePunt(item->getPuntos());
            }
*/
        }
        h->updateTime();
        //valor de interpolacion se actualiza cada render
        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);
       
        
        vista.setCenter(jugador.getPos());
        Window.setView(vista);
       
        
        Window.clear(Color(150, 200, 200));
        Window.draw(map);
        
        jugador.render(interpolacion,tiempoAnimacion);
        Window.draw(enemigo->getAnimacion().getSprite(enemigo->getActual(),enemigo->getframeActual(tiempoAnimacion)));
        enemigo->RenderGranada(Window);
        jugador.RenderDisparo(Window);
        //cout << "VISTA => " << vista.getCenter().x <<  ", " << vista.getCenter().y << endl;
        h->Update(Window, vista);
        jugador.setVidas(h->getContHP());
        
        
        Window.display();
    }
    return 0;
}

