
#include "Jugador.h"
#include "Estado.h"

Jugador::Jugador(int anchura, int altura) {


    tamanyo.x=50;
    tamanyo.y=50;
    cuadrado.setSize(tamanyo);
    cuadrado.setPosition(anchura / 2, altura / 2);
    cuadrado.setFillColor(Color::Blue);
    cuadrado.setOrigin(50 / 2, 50 / 2);
    gravedad=1.5f;
    distanciasuelo=300;
    velocidadsalto=20.0f;
    velocidad.x=0;
    velocidad.y=0;
    
    velocidadm = 600.0f;
    posX = cuadrado.getPosition().x;
    posY = cuadrado.getPosition().y;

}

void Jugador::Movimiento(Time &time) {

    
    float tiempo = time.asSeconds();

    if(Keyboard::isKeyPressed(Keyboard::D))
     cuadrado.move(tiempo * velocidadm, 0);
    if(Keyboard::isKeyPressed(Keyboard::A))
     cuadrado.move(-tiempo * velocidadm, 0);
    
}

void Jugador::Saltar(){
    
    
    if(Keyboard::isKeyPressed(Keyboard::Space) && cuadrado.getPosition().y == distanciasuelo-cuadrado.getSize().y)
    velocidad.y=-velocidadsalto;
    
     
    if(cuadrado.getPosition().y + cuadrado.getSize().y < distanciasuelo || velocidad.y<0){
        
        velocidad.y+=gravedad;
        
   }else{
       
        cuadrado.setPosition(cuadrado.getPosition().x,distanciasuelo-cuadrado.getSize().y);
        velocidad.y=0;
    }
  
    cuadrado.move(velocidad.x,velocidad.y);
}

float Jugador::getposX() {
    
    posX=cuadrado.getPosition().x;
    return posX;

}

float Jugador::getposY() {
    posY=cuadrado.getPosition().y;
    return posY;

}

RectangleShape Jugador::getJugador(){
    
    return cuadrado;
    
}




