#include <iostream>
#include "cabecera.hpp"
#include "Estado.h"
#include "mapaTmx.h"

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
    Time tiempo;

    Int32 tiempoupdate = clock1.getElapsedTime().asMilliseconds();
    int bucle = 0;
    float interpolacion;
    float velocidad = 100.0f;
    float movinterpoladox = 0;
    float movinterpoladoy = 0;
    int cont1 = 0;
    int cont2 = 0;
    //cuadrado
    RectangleShape cuadrado;
    Vector2f tamanyo(50, 50);
    cuadrado.setSize(tamanyo);
    cuadrado.setPosition(anchura / 2, altura / 2);
    cuadrado.setFillColor(Color::Blue);

    Estado nuevo(cuadrado.getPosition().x, cuadrado.getPosition().y);
    Estado viejo(0, 0);

    mapaTmx *m = new mapaTmx();

    while (Window.isOpen()) {
        bucle = 0;
        tiempo = clocl2.restart();
        while (clock1.getElapsedTime().asMilliseconds() > tiempoupdate && bucle < frameskip) {
            tiempoupdate += update;
            bucle++;
            viejo = nuevo;

            Event evento;

            while (Window.pollEvent(evento)) {

                if (evento.type == Event::Closed)
                    Window.close();


                if (Keyboard::isKeyPressed(Keyboard::W))
                    cuadrado.move(0, -tiempo.asSeconds() * velocidad);

                if (Keyboard::isKeyPressed(Keyboard::S))
                    cuadrado.move(0, tiempo.asSeconds() * velocidad);

                if (Keyboard::isKeyPressed(Keyboard::D))
                    cuadrado.move(tiempo.asSeconds() * velocidad, 0);

                if (Keyboard::isKeyPressed(Keyboard::A))
                    cuadrado.move(-tiempo.asSeconds() * velocidad, 0);


            }

            nuevo.actualizartiempo(cuadrado.getPosition().x, cuadrado.getPosition().y);
        }

        interpolacion = float(clock1.getElapsedTime().asMilliseconds() + update - tiempoupdate) / float (update);
        movinterpoladox = InterpolacionRenderx(viejo, nuevo, interpolacion);
        movinterpoladoy = InterpolacionRendery(viejo, nuevo, interpolacion);
        cuadrado.setPosition(movinterpoladox, movinterpoladoy);


        Window.clear(); 
        m->muestraMapa(Window);
        Window.draw(cuadrado);
        Window.display();
    }
    return 0;
}

