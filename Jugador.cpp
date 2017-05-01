
#include "Jugador.h"
#include "Estado.h"
#include "Bala.h"
#include "Granada.h"

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

    velocidadAnimacion=0.1;
    countBala =0;
    if(!TEX.loadFromFile("res/img/SpriteBala.png")){
        std::cerr<<"Error en textura bala";
        exit(0);
    }
    if(!TEX2.loadFromFile("res/img/SpriteGranada.png")){
        std::cerr<<"Error en textura Granada";
        exit(0);
    }
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
   
    posiciones.x=actual;
    posiciones.y=totalSpritesAnimacion;
    animacion->movimiento(movimiento);
}

void Jugador::Saltar() {

     Sprite comprobacion = animacion->getSpriteE();
     velocidadAnimacion=0.3;
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

void Jugador::Disparar(){
    velocidadAnimacion=0.1;
    int speedX=0;
    int speedY=0;
    float balaX = 0;    
    float balaY = 0;
    Vector2f movimiento(0.0f,0.0f);
    if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::A) ) {
        velocidadAnimacion=0.085;
        if(RelojBala.getElapsedTime().asMilliseconds()>500){
            speedY=-10;
            speedX=0;
            balaX=animacion->getSpriteE().getPosition().x-20;
            balaY=animacion->getSpriteE().getPosition().y+50;
            Bala *balaDisparo = new Bala(10,20,speedX, speedY,50);
            balaDisparo->setPosition(balaX,balaY);
            balaDisparo->loadSprite(TEX,0,0);
            CARGADOR.push_back(balaDisparo);
            RelojBala.restart();
        }
        totalSpritesAnimacion = animacion->getNumAnimaciones()[7];
        actual = 7;
    }else if (Keyboard::isKeyPressed(Keyboard::A)) {
            velocidadAnimacion=0.085;
        if(RelojBala.getElapsedTime().asMilliseconds()>500){
            if(animacion->getOrientacion()!=0){
               speedX=10;
               speedY=0;
               balaX=animacion->getSpriteE().getPosition().x+100;
               balaY=animacion->getSpriteE().getPosition().y+200;
            }else{
                speedX=-10;
                speedY=0;
               balaX=animacion->getSpriteE().getPosition().x-100;
               balaY=animacion->getSpriteE().getPosition().y+200;
            }
            Bala *balaDisparo = new Bala(10,20,speedX, speedY,50);
            balaDisparo->setPosition(balaX,balaY);
            balaDisparo->loadSprite(TEX,0,0);
            CARGADOR.push_back(balaDisparo);
                RelojBala.restart();
        }
            totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
            actual = 5;
            movimiento.x=0;
    }
   
    posiciones.x=actual;
    posiciones.y=totalSpritesAnimacion;
    animacion->movimiento(movimiento);
}

void Jugador::DispararGranada(){
    velocidadAnimacion=0.1;
    int speedX=0;
    int speedY=0;
    float GranadaX = 0;    
    float GranadaY = 0;
    Vector2f movimiento(0.0f,0.0f);
    if (Keyboard::isKeyPressed(Keyboard::G)) {
        velocidadAnimacion=0.085;
        if(RelojGranada.getElapsedTime().asMilliseconds()>500){
            if(animacion->getOrientacion()!=0){
               speedX=10;
               speedY=15;
               GranadaX=animacion->getSpriteE().getPosition().x+100;
               GranadaY=animacion->getSpriteE().getPosition().y+200;
            }else{
                speedX=-10;
                speedY=15;
               GranadaX=animacion->getSpriteE().getPosition().x-100;
               GranadaY=animacion->getSpriteE().getPosition().y+200;
            }
            Granada *granadaDisparo = new Granada(18,11,speedX, speedY,60);
            granadaDisparo->setPosition(GranadaX,GranadaY);
            granadaDisparo->loadSprite(TEX2,0,0);
            CARGADORGRANADA.push_back(granadaDisparo);
            RelojGranada.restart();
        }
            totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
            actual = 5;
            movimiento.x=0;
    }
   
    posiciones.x=actual;
    posiciones.y=totalSpritesAnimacion;
    animacion->movimiento(movimiento);
}

void Jugador::UpdateDisparo(){
    int contador=0;
    int move;
    std::vector<Bala*> CargadorAux;
    std::vector<Granada*> CargadorAuxGranada;
    for(contador=0;contador<CARGADOR.size();contador++){
        move=CARGADOR[contador]->move();
        switch(move){
            case 1:
                CargadorAux.push_back(CARGADOR[contador]);
                break;
            case 2:
                CARGADOR[contador]->~Bala();
                break;

            case -1:
                std::cerr<<"Error"<<std::endl;
                break;

        }
    }
    CARGADOR=CargadorAux;
    for(contador=0;contador<CARGADORGRANADA.size();contador++){
        move=CARGADORGRANADA[contador]->move();
        switch(move){
            case 1:
                CargadorAuxGranada.push_back(CARGADORGRANADA[contador]);
                break;
            case 2:
                CARGADORGRANADA[contador]->~Granada();
                break;

            case -1:
                std::cerr<<"Error"<<std::endl;
                break;
        }
    }
    CARGADORGRANADA=CargadorAuxGranada;
    
    
}
void Jugador::RenderDisparo(RenderWindow &window){
    int contador=0;
    for(contador=0;contador<CARGADOR.size();contador++){
        window.draw(CARGADOR[contador]->getSprite());
    }
    for(contador=0;contador<CARGADORGRANADA.size();contador++){
        window.draw(CARGADORGRANADA[contador]->getSprite());
    }
}

float Jugador::getposX() {

    posX = cuadrado.getPosition().x;
    return posX;

}

float Jugador::getposY() {
    posY = cuadrado.getPosition().y;
    return posY;

}

Vector2f Jugador::getPos() {
    return getAnimacion().getSpriteE().getPosition();
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
   
    int frameActual = static_cast<int>((tiempo.asSeconds() / velocidadAnimacion) *  3) %  totalSpritesAnimacion;
    
    return frameActual;
    
}