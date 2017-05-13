

#include "Enemigo.h"

Enemigo::Enemigo() {

    velocidadAnimacion = 0.1;
    animacion = new Animacion("res/img/enemigocomun1.png");
    animacion->spritePersonaje('e');
    
    velocidadmovimiento = 1200.0f;
    
     //Colisiones
    hitBox.setScale(1.5, 2.2);
    hitBox.setSize(Vector2f(32, 32));
    hitBox.setFillColor(Color::Blue);
}

Enemigo::Enemigo(const Enemigo& orig) {
    
}

Enemigo::~Enemigo() {
}

Animacion Enemigo::getAnimacion() {

    return *animacion;

}

void Enemigo::Movimiento(Time &time) {

    float tiempo = time.asSeconds();
    Vector2f movimiento(0.0f, 0.0f);
    actual = 0;
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];


        if (Keyboard::isKeyPressed(Keyboard::L)) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
           actual = 1;
            animacion->orientacion(0);
           movimiento.x= tiempo*velocidadmovimiento;
       }
      
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
            actual = 1;
           animacion->orientacion(1);
            movimiento.x= -tiempo*velocidadmovimiento;
       }
    //    if (Keyboard::isKeyPressed(Keyboard::Down)) {
    //        totalSpritesAnimacion = animacion->getNumAnimaciones()[2];
    //        actual = 2;
    //    }

    animacion->Movimiento(movimiento);
}

int Enemigo::getActual() {

    return actual;
}

int Enemigo::getframeActual(Time& tiempo) {

    int frameActual = static_cast<int> ((tiempo.asSeconds() / velocidadAnimacion) * 3) % totalSpritesAnimacion;

    return frameActual;

}