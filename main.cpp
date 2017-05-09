#include "cabecera.hpp"
#include "mapaTmx.h"
#include "Estado.h"
#include "MovimientoIA.h"
#include "Jugador.h"
#include "hud.h"
#include "ObjetoPuntuacion.h"
#include "Enemigo.h"

const int update = 1000 / 25;
const int frameskip = 5;
int anchura = 1270;
int altura = 720;

float InterpolacionRenderx(Estado& Anterior, Estado& Nuevo, float interpolacion) {

    float movimientox = Anterior.getx()*(1 - interpolacion) + Nuevo.getx() * interpolacion;
    return movimientox;
}

float InterpolacionRendery(Estado& Anterior, Estado& Nuevo, float interpolacion) {

    float movimientoy = Anterior.gety()*(1 - interpolacion) + Nuevo.gety() * interpolacion;
    return movimientoy;
}

int main() {
    RenderWindow Window(VideoMode(anchura, altura), "Test");
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

    while (Window.isOpen()) {
        bucle = 0;
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoAnimacion += tiempo;
            tiempoupdate += update;
            bucle++;
            //estados
            viejo = nuevo;

            Event evento;
            while (Window.pollEvent(evento)) {
                if (evento.type == Event::Closed)
                    Window.close();
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
        movinterpoladox = InterpolacionRenderx(viejo, nuevo, interpolacion);
        movinterpoladoy = InterpolacionRendery(viejo, nuevo, interpolacion);

        
        
        vista.setCenter(Vector2f(jugador.getPos().x, vista.getCenter().y));
        Window.setView(vista);

        jugador.getAnimacion().MovimientoInterpolado(Vector2f(movinterpoladox, movinterpoladoy));

        Window.clear(Color(150, 200, 200));
        
        
        Window.draw(map);
        Window.draw(jugador.getAnimacion().getSprite(jugador.getActual(), jugador.getframeActual(tiempoAnimacion)));
        Window.draw(enemigo.getAnimacion().getSprite(0,0));
        
        jugador.RenderDisparo(Window);
        for (int n = 0; n < h->getContHP(); n++) {
            Window.draw(h->getPlayerHP(n));
        }
        if (item->getRecogido() == false)
            Window.draw(item->getSprite());

        //Window.draw(rectangulo);
        Window.draw(h->getTextVida());
        Window.draw(h->getArma());
        Window.draw(h->getGranada());
        Window.draw(h->getTextArma());
        Window.draw(h->getIcono());
        Window.draw(h->getTextPunt());
        Window.draw(h->getTextTime());
        Window.draw(h->getTextGranada());
        Window.display();
    }
    return 0;
}

