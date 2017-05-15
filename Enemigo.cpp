
#include <stdlib.h> 
#include <cmath>
#include <valarray> 
#include "Enemigo.h"

Enemigo::Enemigo() {

    velocidadAnimacion = 0.1;
    animacion = new Animacion("res/img/enemigocomun1.png");
    animacion->spritePersonaje('e');
    c = new sf::Clock();
    time1=0;
    time_aux=-1;
    velocidadmovimiento = 600.0f;
    
     //Colisiones
    hitBox.setScale(1.5, 2.2);
    hitBox.setSize(Vector2f(32, 32));
    hitBox.setFillColor(Color::Blue);
    random=3;
    sorpresa=false;
}

Enemigo::Enemigo(const Enemigo& orig) {
    
}

Enemigo::~Enemigo() {
}

Animacion Enemigo::getAnimacion() {

    return *animacion;

}

void Enemigo::Movimiento(Time &time, Jugador jugador) {

    float tiempo = time.asSeconds();
    Vector2f movimiento(0.0f, 0.0f);
    Vector2f posJugador=jugador.getPos();
    Vector2f posEnemigo = animacion->getSpriteE().getPosition();
    float dif = posJugador.x-posEnemigo.x;
    actual = 0;
    
    time1 = c->getElapsedTime().asSeconds();
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
    velocidadmovimiento = 600.0f;
    if(abs(dif)>320){
         
        if (time_aux==-1 || time1==time_aux){
            random = rand()%3;
            time_aux=time1+1;
        }
        if (random==1) {
           totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
           actual = 1;
           animacion->orientacion(0);
           movimiento.x= tiempo*velocidadmovimiento;
        }
      
        if (random==0) {          
            totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
            actual = 1;
            animacion->orientacion(1);
            movimiento.x= -tiempo*velocidadmovimiento;
        }
    
    }else{
        time_aux=time1;
        if(abs(dif)>140){
            if(!sorpresa){
                sorpresa=true;
              
                  velocidadAnimacion = 0.5;
                if(posJugador.x<posEnemigo.x){
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
                    actual = 3;
                    animacion->orientacion(1);
                }else{
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
                    actual = 3;
                    animacion->orientacion(0);
                }
            }else{
                  velocidadAnimacion = 0.1;
                     velocidadmovimiento = 1000.0f;
                if(posJugador.x<posEnemigo.x){
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                    actual = 1;
                   animacion->orientacion(1);
                    movimiento.x= -tiempo*velocidadmovimiento;
                }else{
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                   actual = 1;
                    animacion->orientacion(0);
                   movimiento.x= tiempo*velocidadmovimiento;
                }
            }
        }else{
            if(posJugador.x<posEnemigo.x){
                totalSpritesAnimacion = animacion->getNumAnimaciones()[4];
                actual = 4;
                animacion->orientacion(1);
                
            }else{
               totalSpritesAnimacion = animacion->getNumAnimaciones()[4];
               actual = 4;
               animacion->orientacion(0);

            }
        }
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