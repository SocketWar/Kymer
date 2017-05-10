
#include "Jugador.h"
#include "Estado.h"
#include "Bala.h"
#include "Granada.h"

Jugador::Jugador(int anchura, int altura) {
    
    gravedad = 2.0f;
    distanciasuelo = 700;
    velocidadsalto = 30.0f;
    velocidad.x = 0;
    velocidad.y = 0;
    
    velocidadanimacion=0.1;
    velocidadmovimiento = 1200.0f;

    //Sprites
    animacion = new Animacion("res/img/PersonajeFull.png");
    animacion->spritePersonaje('p');
    velocidadAnimacion=0.1;
    countBala =0;
    
    //Estados
    viejo= new Estado();
    nuevo= new Estado();
    //Colisiones
    hitBox.setScale(1.5, 2.2);
    hitBox.setSize(Vector2f(32, 32));
    hitBox.setFillColor(Color::Blue);
    
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
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
    hitBox.setScale(1.5,2.2);
    hitBox.setPosition(getPos().x-25,getPos().y-70);
    
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
        hitBox.setScale(1.5,1.5);
        hitBox.setPosition(getPos().x-25,getPos().y-48);
        totalSpritesAnimacion = animacion->getNumAnimaciones()[2];
        actual = 2;
        
    }
     
    animacion->Movimiento(movimiento);
}

void Jugador::Saltar() {

    float posicion = animacion->getSpriteE().getGlobalBounds().top+animacion->getSpriteE().getGlobalBounds().height;
    //cout<<"posicion de los pies"<<posicion<<endl;
     velocidadAnimacion=0.3;
     
     if(!colision){
         suelo=false;
     }
     
    if (Keyboard::isKeyPressed(Keyboard::Space) && suelo){
        velocidad.y = -velocidadsalto;
        
        
    }else if (!suelo) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
        actual = 3;
        velocidad.y += gravedad;
    } else {
       //animacion->MovimientoInterpolado(Vector2f(getPos().x, distanciasuelo-animacion->getSpriteE().getScale().y));
        velocidad.y = 0;
        
    }

        animacion->Movimiento(velocidad);
}

void Jugador::Disparar(){
    velocidadAnimacion=0.1;
    int speedX=0;
    int speedY=0;
    float balaX = 0;    
    float balaY = 0;
     
    if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::A)) {
        velocidadAnimacion=0.085;
        if(RelojBala.getElapsedTime().asMilliseconds()>500){
            speedY=-30;
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
        if(Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::Right) && distanciasuelo==(getPos().y+2)){
            
            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
            actual = 8;
            
            
        }else if(Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::Left) && distanciasuelo==(getPos().y+2)){
            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
            actual = 8;
           
        }else if(Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::Down) && distanciasuelo==(getPos().y+2)){
            
            totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
            actual = 6;
            
        }else{
            totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
            actual = 5;
        }
        if(RelojBala.getElapsedTime().asMilliseconds()>500){
            if(animacion->getOrientacion()!=0){
               speedX=30;
               speedY=0;
               balaX=animacion->getSpriteE().getPosition().x+100;
               balaY=animacion->getSpriteE().getPosition().y+200;
            }else{
                speedX=-30;
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
            
    }
   
   
    
}

void Jugador::DispararGranada(){
    velocidadAnimacion=0.1;
    int speedX=0;
    int speedY=0;
    float GranadaX = 0;    
    float GranadaY = 0;
    
    if (Keyboard::isKeyPressed(Keyboard::G)) {
        velocidadAnimacion=0.1;
        
        if(Keyboard::isKeyPressed(Keyboard::G) && Keyboard::isKeyPressed(Keyboard::Right) && distanciasuelo==(getPos().y+2)){
            totalSpritesAnimacion = animacion->getNumAnimaciones()[12];
            actual = 12;
            
        }else if(Keyboard::isKeyPressed(Keyboard::G) && Keyboard::isKeyPressed(Keyboard::Left) && distanciasuelo==(getPos().y+2)){
            totalSpritesAnimacion = animacion->getNumAnimaciones()[12];
            actual = 12;
           
        }else if(Keyboard::isKeyPressed(Keyboard::G) && Keyboard::isKeyPressed(Keyboard::Down) && distanciasuelo==(getPos().y+2)){
            totalSpritesAnimacion = animacion->getNumAnimaciones()[13];
            actual = 13;
        }else{
            totalSpritesAnimacion = animacion->getNumAnimaciones()[11];
            actual = 11;
        }
        
        if(RelojGranada.getElapsedTime().asMilliseconds()>600){
            if(animacion->getOrientacion()!=0){
               speedX=10;
               speedY=15;
               GranadaX=animacion->getSpriteE().getPosition().x+50;
               GranadaY=animacion->getSpriteE().getPosition().y+200;
            }else{
                speedX=-10;
                speedY=15;
               GranadaX=animacion->getSpriteE().getPosition().x-50;
               GranadaY=animacion->getSpriteE().getPosition().y+200;
            }
            Granada *granadaDisparo = new Granada(18,11,speedX, speedY,60);
            granadaDisparo->setPosition(GranadaX,GranadaY);
            granadaDisparo->loadSprite(TEX2,0,0);
            CARGADORGRANADA.push_back(granadaDisparo);
            RelojGranada.restart();
        }
            
           
    }
   
   
   
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

Vector2f Jugador::getPos() {
    return animacion->getSpriteE().getPosition();
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

void Jugador::actualizarEstado(){
    
    viejo=nuevo;
    
}

void Jugador::setEstado(){
    
    nuevo->actualizartiempo(getPos().x,getPos().y);
    
}

Estado* Jugador::getViejo(){
    
    
    return viejo;
}

Estado* Jugador::getNuevo(){
    
    return nuevo;
}


void Jugador::setVidas(int i){
    vidas=i;
}

int Jugador::getVidas(){
    return vidas;
}

RectangleShape Jugador::gethitBox(){
    
    return hitBox;
}

void Jugador::calcularColision(FloatRect** arrayColisiones,int nobjetos){
    // ALTO = 40PX
    // ANCHO = 35PX
    float posicion = animacion->getSpriteE().getGlobalBounds().top+animacion->getSpriteE().getGlobalBounds().height;
    for(int i=0;i<nobjetos-2;i++){
        FloatRect* a = arrayColisiones[i];
        if(a->intersects(hitBox.getGlobalBounds())){
            
            cout << "posicion a " << a->top << " PJ " << hitBox.getGlobalBounds().height + hitBox.getGlobalBounds().top << endl;
           
                colision=true;
                suelo=true;
            
        }else{
                colision=false;
        }
        
        cout<<"el suelo es:"<<suelo<<endl;
            //cout << "i: " << i << " => " << a->left << ", " << a->top << " [" << a->width << ", " << a->height << "]" << endl;
    }
    //cout << endl;
}