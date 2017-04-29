
#include "Jugador.h"
#include "Estado.h"

Jugador::Jugador(int anchura, int altura, string enlace) {
    
    gravedad = 2.0f;
    distanciasuelo = 322;
    velocidadsalto = 30.0f;
    velocidad.x = 0;
    velocidad.y = 0;
    
    velocidadanimacion=0.1;
    velocidadmovimiento = 800.0f;
    posX = cuadrado.getPosition().x;
    posY = cuadrado.getPosition().y;


    animacion = new Animacion(enlace);
    animacion->spritePersonaje();

}

void Jugador::Movimiento(Time &time) {

    float tiempo = time.asSeconds();
    
    Vector2f movimiento(0.0f,0.0f);
    actual = 0;
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];;

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
        actual = 1;
        animacion->orientacion(1);
        movimiento.x= tiempo*velocidadmovimiento;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
        actual = 1;
        animacion->orientacion(0);
        movimiento.x= -tiempo*velocidadmovimiento;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[2];
        actual = 2;
    }   
    if (Keyboard::isKeyPressed(Keyboard::A)) {

        totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
        actual = 5;
        movimiento.x=0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::A) ) {
        
        totalSpritesAnimacion = animacion->getNumAnimaciones()[7];
        actual = 7;
    }
   
    posiciones.x=actual;
    posiciones.y=totalSpritesAnimacion;
    animacion->movimiento(movimiento);
}

void Jugador::Saltar() {

     Sprite comprobacion = animacion->getSpriteE();
        
    if (Keyboard::isKeyPressed(Keyboard::Space) && comprobacion.getPosition().y == distanciasuelo){
        velocidad.y = -velocidadsalto;
        posiciones.x=actual;
        posiciones.y=totalSpritesAnimacion;
    }

     if(comprobacion.getPosition().y!=distanciasuelo){
         
         totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
            actual = 3;
     }
         
    if (comprobacion.getPosition().y + comprobacion.getScale().y < distanciasuelo || velocidad.y < 0) {

        velocidad.y += gravedad;

    } else {

        comprobacion.setPosition(comprobacion.getPosition().x, distanciasuelo-comprobacion.getScale().y);
        velocidad.y = 0;

    }

        animacion->movimiento(velocidad);
}

float Jugador::getposX() {

    posX = cuadrado.getPosition().x;
    return posX;

}

float Jugador::getposY() {
    posY = cuadrado.getPosition().y;
    return posY;

}

RectangleShape Jugador::getJugador() {

    return cuadrado;

}

Animacion Jugador::getAnimacion(){
    
    return *animacion;
    
}

int Jugador::getActual(){
    
    return actual;
}

int Jugador::gettotalSpritesAnimacion(){
    
    return totalSpritesAnimacion;
}

int Jugador::getframeActual(Time& tiempo){
   
    int frameActual = static_cast<int>((tiempo.asSeconds() / 0.1) *  3) %  totalSpritesAnimacion;
    
    return frameActual;
    
}