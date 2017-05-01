#include "cabecera.hpp"
#include "mapaTmx.h"
#include "Estado.h"
#include "MovimientoIA.h"
#include "Jugador.h"

const int update = 1000 / 25;
const int frameskip = 5;
int anchura = 800;
int altura = 600;

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

    //clock update y movimiento
    Clock clock1;
    Clock clocl2;
    Clock relojBala;
    Time tiempoBala;
    float countBala=0;
    Time tiempo;
    Time tiempoAnimacion;
    
    Int32 tiempoupdate = clock1.getElapsedTime().asMilliseconds();
    int bucle = 0;
    float interpolacion;
    float movinterpoladox = 0;
    float movinterpoladoy = 0;
    
    Jugador jugador(anchura,altura,"res/img/Personajev1.png");
    Estado nuevo(jugador.getposX(), jugador.getposY());
    Estado viejo(0, 0);


    mapaTmx map;

    View vista(jugador.getPos(), Vector2f(anchura, altura));
    cout << "CENTRO DE LA VISTA: " << vista.getCenter().x << ", " << vista.getCenter().y << endl;
    
    while (Window.isOpen()) {
         bucle = 0;
        tiempoBala=relojBala.getElapsedTime();
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoAnimacion+=tiempo;
            tiempoupdate += update;
            bucle++;
            
            viejo = nuevo;
           
            Event evento;
            while (Window.pollEvent(evento)) {

                if (evento.type == Event::Closed)
                    Window.close();  
            }
            
            jugador.Movimiento(tiempo);
            jugador.Saltar();
            
            jugador.Disparar();
            jugador.UpdateDisparo();
            
            jugador.DispararGranada();
            
            //movimiento.movimentoIA(tiempo, trol.getJugador(), cuadrado2);
            //movimiento.esquivarIA(tiempo,trol.getJugador(),cuadrado2);
            nuevo.actualizartiempo(jugador.getposX(), jugador.getposY());
        }

        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);
        movinterpoladox = InterpolacionRenderx(viejo, nuevo, interpolacion);
        movinterpoladoy = InterpolacionRendery(viejo, nuevo, interpolacion);
        
        vista.setCenter(jugador.getPos());
        Window.setView(vista);

        jugador.getJugador().setPosition(movinterpoladox, movinterpoladoy);
        Window.clear(Color(150, 200, 200)); 
        Window.draw(map);
        Window.draw(jugador.getAnimacion().getSprite(jugador.getActual(),jugador.getframeActual(tiempoAnimacion)));
        jugador.RenderDisparo(Window);
        Window.display();
    }
    return 0;
}

