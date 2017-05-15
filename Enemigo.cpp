
#include <stdlib.h> 
#include <cmath>
#include <valarray> 
#include "Enemigo.h"

Enemigo::Enemigo(int tipoE) {

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
    tipo=tipoE;
    /*
     * 1 Granada
     * 2 Metralleta
     * 3 Mortero
     * 4 Banzai 
     */
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
    
    time1 = c->getElapsedTime().asSeconds();
    actual = 0;
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
    velocidadmovimiento = 600.0f;
    //Enemigo granada
    if(tipo==1 || tipo==3){
        if(abs(dif)>500){
            //Movimiento random
            sorpresa=false;
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
            if(actual==3)
                time_aux=time1;
            if(abs(dif)>400){
                //Sorpresa al ver a jugador
                if(!sorpresa){
                    if(time_aux==time1)
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
                    //Movimiento a jugador
                    //time_aux=time1;
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
                if(abs(dif)>250){
                    if(tipo!=3){
                        //Lanzar Granada a jugador
                        int speedX = 0;
                        int speedY = 0;
                        float GranadaX = 0;
                        float GranadaY = 0;
                        velocidadAnimacion = 0.05;
                        if(posJugador.x<posEnemigo.x){
                            totalSpritesAnimacion = animacion->getNumAnimaciones()[4];
                            actual = 4;
                            animacion->orientacion(1);
                            speedX = -10;
                            speedY = 15;
                            GranadaX = posEnemigo.x;
                            GranadaY = posEnemigo.y -60;

                        }else{
                           totalSpritesAnimacion = animacion->getNumAnimaciones()[4];
                           actual = 4;
                           animacion->orientacion(0);
                            speedX = 10;
                            speedY = 15;
                            GranadaX = animacion->getSpriteE().getPosition().x + 40;
                            GranadaY = animacion->getSpriteE().getPosition().y -60;

                        }
                        if (RelojGranada.getElapsedTime().asMilliseconds() > 1100) {
                            Texture TEX2;
                            if (!TEX2.loadFromFile("res/img/SpriteGranada.png")) {
                                std::cerr << "Error en textura Granada";
                                exit(0);
                            }
                            Granada *granadaDisparo = new Granada(18, 11, speedX, speedY, 60);
                            granadaDisparo->setPosition(GranadaX, GranadaY);
                            granadaDisparo->loadSprite(TEX2, 0, 0);
                            CARGADORGRANADA.push_back(granadaDisparo);
                            RelojGranada.restart();
                            std::cout<<"Boom"<<std::endl;
                        }
                    }else{
                        //Lanzar Mortero a jugador
                        int speedX = 0;
                        int speedY = 0;
                        float morteroX = 0;
                        float morteroY = 0;
                        velocidadAnimacion = 0.05;
                        if(posJugador.x<posEnemigo.x){
                            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
                            actual = 8;
                            animacion->orientacion(1);
                            speedX = -10;
                            speedY = 15;
                            morteroX = posEnemigo.x;
                            morteroY = posEnemigo.y -60;

                        }else{
                           totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
                           actual = 8;
                           animacion->orientacion(0);
                            speedX = 10;
                            speedY = 15;
                            morteroX = animacion->getSpriteE().getPosition().x + 40;
                            morteroY = animacion->getSpriteE().getPosition().y -60;

                        }
                        if (RelojGranada.getElapsedTime().asMilliseconds() > 1100) {
                            Texture TEX2;
                            if (!TEX2.loadFromFile("res/img/SpriteGranada.png")) {
                                std::cerr << "Error en textura Granada";
                                exit(0);
                            }
                            Granada *granadaDisparo = new Granada(18, 11, speedX, speedY, 60);
                            granadaDisparo->setPosition(morteroX, morteroY);
                            granadaDisparo->loadSprite(TEX2, 0, 0);
                            CARGADORGRANADA.push_back(granadaDisparo);
                            RelojGranada.restart();
                            std::cout<<"Boom"<<std::endl;
                        }
                    }
                }else{
                    //Movimiento a jugador
                      velocidadAnimacion = 0.1;
                         velocidadmovimiento = 850.0f;
                    if(posJugador.x>posEnemigo.x){
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
            }
        }
    }else{
        actual = 5;
        totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
        //Enemigo metralleta
        if(tipo==2){
            if(abs(dif)>320){
            //Movimiento random
            sorpresa=false;
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
                if(actual==3)
                    time_aux=time1;
                if(abs(dif)>140){
                    //Sorpresa al ver a jugador
                    if(!sorpresa){
                        if(time_aux==time1)
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
                        //Movimiento a jugador
                        time_aux=time1;
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
                    //Disparar a jugador
                    int speedX = 0;
                    int speedY = 0;
                    float balaX = 0;
                    float balaY = 0;
                    velocidadAnimacion = 0.1;
                    if(posJugador.x<posEnemigo.x){
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
                        actual = 6;
                        animacion->orientacion(1);
                        speedX = -10;
                        balaX = posEnemigo.x;
                        balaY = posEnemigo.y -60;

                    }else{
                       totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
                       actual = 6;
                       animacion->orientacion(0);
                        speedX = 10;
                        balaX = animacion->getSpriteE().getPosition().x + 40;
                        balaY = animacion->getSpriteE().getPosition().y -60;

                    }
                    if (RelojBala.getElapsedTime().asMilliseconds() > 800) {
                        Texture TEX;
                        if (!TEX.loadFromFile("res/img/SpriteBala.png")) {
                            std::cerr << "Error en textura bala";
                            exit(0);
                        }
                        Bala *balaDisparo = new Bala(9, 23, speedX, speedY, 50);
                        balaDisparo->setPosition(balaX, balaY);
                        balaDisparo->loadSprite(TEX, 0, 0);
                        CARGADOR.push_back(balaDisparo);
                        RelojBala.restart();
                    }
                }
            }
        }
    }
    animacion->Movimiento(movimiento);
}

void Enemigo::UpdateGranada() {
    int contador = 0;
    int move;
    std::vector<Granada*> CargadorAuxGranada;
    std::vector<Bala*> CargadorAux;
    for (contador = 0; contador < CARGADOR.size(); contador++) {
        move = CARGADOR[contador]->move();
        switch (move) {
            case 1:
                CargadorAux.push_back(CARGADOR[contador]);
                break;
            case 2:
                CARGADOR[contador]->~Bala();
                break;

            case -1:
                std::cerr << "Error" << std::endl;
                break;

        }
    }
    CARGADOR = CargadorAux;
    for (contador = 0; contador < CARGADORGRANADA.size(); contador++) {
        move = CARGADORGRANADA[contador]->move();
        switch (move) {
            case 1:
                CargadorAuxGranada.push_back(CARGADORGRANADA[contador]);
                break;
            case 2:
                CARGADORGRANADA[contador]->~Granada();
                break;

            case -1:
                std::cerr << "Error" << std::endl;
                break;
        }
    }
    CARGADORGRANADA = CargadorAuxGranada;
}

void Enemigo::RenderGranada(RenderWindow &window) {
    int contador = 0;
    for (contador = 0; contador < CARGADOR.size(); contador++) {
        window.draw(CARGADOR[contador]->getSprite());
    }
    for (contador = 0; contador < CARGADORGRANADA.size(); contador++) {
        window.draw(CARGADORGRANADA[contador]->getSprite());
    }
}


int Enemigo::getActual() {

    return actual;
}

int Enemigo::getframeActual(Time& tiempo) {

    int frameActual = static_cast<int> ((tiempo.asSeconds() / velocidadAnimacion) * 3) % totalSpritesAnimacion;

    return frameActual;

}void Enemigo::update(Time &tiempo, Jugador jugador){
    
    
            viejo=nuevo;
            Movimiento(tiempo,jugador);
            //Saltar();
            //Disparar();
            UpdateGranada();
            //DispararGranada();
            //nuevo->actualizartiempo(getPos().x,getPos().y);
            
}



void Enemigo::render(float interpolacion,Time &tiempo){
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& Window= motor->getWindow();
    
    //actualizarHitbox();
    animacion->MovimientoInterpolado(viejo->getInterpolacion(viejo,nuevo,interpolacion));
    Window.draw(animacion->getSprite(actual, getframeActual(tiempo)));
    //Window.draw(hitBox);
    
}