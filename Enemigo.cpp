
#include <stdlib.h> 
#include <cmath>
#include <valarray> 
#include "Enemigo.h"

Enemigo::Enemigo(int tipoE, float posx, float posy) {

    vidas = 10;

    velocidadAnimacion = 0.1;
    if (tipoE != 4) {
        animacion = new Animacion("res/img/enemigocomun1.png", posx, posy);
        animacion->spritePersonaje('e');
        sonidoMuerte= new sonido();//sera el mismo para todos excepto la vaca
        sonidoMuerte->setSonido("res/audio/enemyDead.wav");
        sonidoMuerte->getSonido().setLoop(false);
        sonidoMuerte->setReproduccion(0);//solo se reproducira 1 vez
        if(tipoE==1){//enemigo lanzagranadas
            sonidoAtaque = new sonido();
            sonidoAtaque->setSonido("res/audio/FireInTheHole.wav");
            sonidoAtaque->getSonido().setLoop(false);
            sonidoAtaque->setReproduccion(0);//0 se preproduce, 1 no
           
        }
        if(tipoE==2){//enemigo metralleta
            sonidoAtaque = new sonido();
            sonidoAtaque->setSonido("res/audio/shot.wav");
            sonidoAtaque->getSonido().setLoop(false);
            sonidoAtaque->setReproduccion(0);//o se preproduce, 1 no
        }
        if(tipoE==3){//enemigo mortero
            sonidoAtaque = new sonido();
            sonidoAtaque->setSonido("res/audio/Fireee.wav");
            sonidoAtaque->getSonido().setLoop(false);
            sonidoAtaque->setReproduccion(0);//o se preproduce, 1 no
        }
    } else {//vaca
        animacion = new Animacion("res/img/VacaBurra.png", posx, posy);
        animacion->spritePersonaje('v');
        hitBoxataqueVaca.setScale(0, 0);
        hitBoxataqueVaca.setSize(Vector2f(12, 12));
        hitBoxataqueVaca.setFillColor(Color::Blue);
        sonidoAtaque = new sonido();
        sonidoAtaque->setSonido("res/audio/cow.wav");
        sonidoAtaque->getSonido().setLoop(false);
        
        sonidoMuerte= new sonido();
        sonidoMuerte->setSonido("res/audio/Cowdead.wav");
        sonidoMuerte->getSonido().setLoop(false);
        sonidoMuerte->setReproduccion(0);//solo se reproducira 1 vez
    }

    c = new sf::Clock();
    time1 = 0;
    time_aux = -1;
    velocidadmovimiento = 2000.0f;
    gravedad = 2.0f;
    distanciasuelo = 700;
    velocidadsalto = 20.0f;
    velocidad.x = 0;
    velocidad.y = 0;

    //Estados
    viejo = new Estado();
    nuevo = new Estado();

    //Colisiones
    hitBox.setScale(3, 2.2);
    hitBox.setSize(Vector2f(32, 32));
    hitBox.setFillColor(Color::Blue);
    muro = false;
    random = 3;
    sorpresa = false;
    tipo = tipoE;
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

void Enemigo::Movimiento(Time &time, Time &tiempoanimacion, Jugador jugador) {

    float tiempo = time.asSeconds();
    Vector2f movimiento(0.0f, 0.0f);
    Vector2f posJugador = jugador.getPos();
    Vector2f posEnemigo = animacion->getSpriteE().getPosition();
    float dif = posJugador.x - posEnemigo.x;
    float dify = posJugador.y - posEnemigo.y;

    time1 = c->getElapsedTime().asSeconds();
    actual = 0;
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
    //velocidadmovimiento = 600.0f;
    //Enemigo granada
    if (tipo == 1) {
        if (abs(dif) > 480 || abs(dify) > 200) {
            //Movimiento random
            sorpresa = false;
             sonidoAtaque->setReproduccion(0);//cuando no tira la granada se vuelve a 0 para reproducir soniso
            if (c->getElapsedTime().asMilliseconds() > 1000) {

                if (time_aux == -1 || time1 == time_aux) {
                    random = rand() % 3;
                    time_aux = time1 + 1;
                }
            }
            if (random == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
                animacion->orientacion(0);
                if (!muro) {
                    movimiento.x = tiempo*velocidadmovimiento;
                } else {
                    movimiento.x = 0;
                }
            }

            if (random == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
                animacion->orientacion(1);
                if (!muro) {
                    movimiento.x = -tiempo*velocidadmovimiento;
                } else {
                    movimiento.x = 0;
                }
            }

        } else {
            if (actual == 3)
                time_aux = time1;
            if (abs(dif) > 400 || abs(dify) > 200) {
                //Sorpresa al ver a jugador
                if (!sorpresa) {
                    if (time_aux == time1)
                        sorpresa = true;

                    velocidadAnimacion = 0.5;
                    if (posJugador.x < posEnemigo.x) {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
                        actual = 3;
                        animacion->orientacion(1);
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
                        actual = 3;
                        animacion->orientacion(0);
                    }
                } else {
                    //Movimiento a jugador
                    time_aux = time1;
                    velocidadAnimacion = 0.1;
                    velocidadmovimiento = 1500.0f;
                    sonidoAtaque->setReproduccion(0);//cuando no tira la granada se vuelve a 0 para reproducir soniso
                    if (posJugador.x < posEnemigo.x) {
                        
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(1);
                        if (!muro) {
                            movimiento.x = -tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(0);
                        if (!muro) {
                            movimiento.x = tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    }
                }
            } else {
                if (abs(dif) > 250 || abs(dify) > 200) {
                    time_aux = time1;
                    if (tipo != 3) {
                        //Lanzar Granada a jugador
                        int speedX = 0;
                        int speedY = 0;
                        float GranadaX = 0;
                        float GranadaY = 0;
                        velocidadAnimacion = 0.1;
                        velocidadmovimiento = 180.0f;
                        if (posJugador.x < posEnemigo.x) {
                            
                            if(sonidoAtaque->getReproduccion()==0){//solo reproduzco si es la primera vez que lanza granada despues de ver al jugador
                                sonidoAtaque->reproducir();
                                 sonidoAtaque->setReproduccion(1);
                               
                            }
                            totalSpritesAnimacion = animacion->getNumAnimaciones()[4];
                            actual = 4;
                            animacion->orientacion(1);
                            speedX = -9;
                            speedY = 15;
                            GranadaX = posEnemigo.x;
                            GranadaY = posEnemigo.y - 60;

                        } else {
                            if(sonidoAtaque->getReproduccion()==0){//solo reproduzco si es la primera vez que lanza granada despues de ver al jugador
                                sonidoAtaque->reproducir();
                                 sonidoAtaque->setReproduccion(1);
                               
                            }
                            totalSpritesAnimacion = animacion->getNumAnimaciones()[4];
                            actual = 4;
                            animacion->orientacion(0);
                            speedX = 9;
                            speedY = 15;
                            GranadaX = animacion->getSpriteE().getPosition().x + 40;
                            GranadaY = animacion->getSpriteE().getPosition().y - 60;

                        }
                        if (RelojGranada.getElapsedTime().asMilliseconds() > 1100) {
                            Texture TEX2;
                            if (!TEX2.loadFromFile("res/img/SpriteGranada.png")) {
                                std::cerr << "Error en textura Granada";
                                exit(0);
                            }

                            if (abs(dif) < 350 && abs(dify) < 200) {
                                if (posJugador.x < posEnemigo.x) {
                                    speedX = speedX + 5;

                                } else {
                                    speedX = speedX - 5;
                                }

                            }
                            Granada *granadaDisparo = new Granada(18, 11, speedX, speedY, 60);
                            granadaDisparo->setPosition(GranadaX, GranadaY);
                            granadaDisparo->loadSprite(TEX2, 0, 0);
                            CARGADORGRANADA.push_back(granadaDisparo);
                            RelojGranada.restart();

                        }
                    }
                } else {
                    time_aux = time1;
                    //Movimiento a jugador
                    velocidadAnimacion = 0.1;
                    velocidadmovimiento = 800.0f;
                    if (posJugador.x > posEnemigo.x) {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(1);
                        if (!muro) {
                            movimiento.x = -tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(0);
                        if (!muro) {
                            movimiento.x = tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    }

                }
            }
        }
        //enemigo escopeta
    } else if (tipo == 2) {
        actual = 5;
        totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
        if (abs(dif) > 320 || abs(dify) > 200) {
            //Movimiento random
            sorpresa = false;
            if (c->getElapsedTime().asMilliseconds() > 1000) {
                if (time_aux == -1 || time1 == time_aux) {
                    random = rand() % 3;
                    time_aux = time1 + 1;
                }
            }
            if (random == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
                animacion->orientacion(0);
                if (!muro) {
                    movimiento.x = tiempo*velocidadmovimiento;
                } else {
                    movimiento.x = 0;
                }
            }

            if (random == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
                animacion->orientacion(1);
                if (!muro) {
                    movimiento.x = -tiempo*velocidadmovimiento;
                } else {
                    movimiento.x = 0;
                }
            }

        } else {
            if (actual == 3)
                time_aux = time1;
            if (abs(dif) > 200 || abs(dify) < 200 && abs(dify) > 50) {
                //Sorpresa al ver a jugador
                if (!sorpresa) {
                    if (time_aux == time1)
                        sorpresa = true;

                    velocidadAnimacion = 0.4;
                    if (posJugador.x < posEnemigo.x) {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
                        actual = 3;
                        animacion->orientacion(1);
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
                        actual = 3;
                        animacion->orientacion(0);
                    }
                } else {
                    //Movimiento a jugador
                    time_aux = time1;
                    velocidadAnimacion = 0.1;
                    velocidadmovimiento = 2500.0f;
                    if (posJugador.x < posEnemigo.x) {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(1);
                        if (!muro) {
                            movimiento.x = -tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(0);
                        if (!muro) {
                            movimiento.x = tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    }
                }
            } else {
                //Disparar a jugador
                time_aux = time1;
                int speedX = 0;
                int speedY = 0;
                float balaX = 0;
                float balaY = 0;
                velocidadAnimacion = 0.1;
                if (posJugador.x < posEnemigo.x) {
                    sonidoAtaque->reproducir();
                            
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
                    actual = 6;
                    animacion->orientacion(1);
                    speedX = -15;
                    balaX = posEnemigo.x;
                    balaY = posEnemigo.y - 60;

                } else {
                    sonidoAtaque->reproducir();
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
                    actual = 6;
                    animacion->orientacion(0);
                    speedX = 15;
                    balaX = animacion->getSpriteE().getPosition().x + 40;
                    balaY = animacion->getSpriteE().getPosition().y - 60;

                }
                if (RelojBala.getElapsedTime().asMilliseconds() > 800) {
                    Texture TEX;
                    if (!TEX.loadFromFile("res/img/balada2.png")) {
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
    } else if (tipo == 3) {
        //Lanzar Mortero a jugador
        int speedX = -9;
        int speedY = 15;
        float morteroX = 0;
        float morteroY = 0;
        int vx = 40;
        int vy = 60;
        velocidadAnimacion = 0.07;
   
            sonidoAtaque->setReproduccion(0);
        
        if (posJugador.x < posEnemigo.x) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
            actual = 8;
            animacion->orientacion(1);

            morteroX = posEnemigo.x;
            morteroY = posEnemigo.y - vy;

        } else {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
            actual = 8;
            animacion->orientacion(0);
            speedX = speedX*-1;

            morteroX = animacion->getSpriteE().getPosition().x + vx;
            morteroY = animacion->getSpriteE().getPosition().y - vy;

        }
        if (abs(dif) < 640 && abs(dify) < 200) {
            if (RelojGranada.getElapsedTime().asMilliseconds() > 1100) {

                Texture TEX2;
                if (!TEX2.loadFromFile("res/img/bala_mortero.png")) {
                    std::cerr << "Error en textura Granada";
                    exit(0);
                }
                if (abs(dif) < 200 && abs(dify) < 200) {
                    if (posJugador.x < posEnemigo.x) {
                        speedX = speedX + 6;

                    } else {
                        speedX = speedX - 6;
                    }

                }
                if (abs(dif) < 350 && abs(dify) < 200) {
                    if (posJugador.x < posEnemigo.x) {
                        speedX = speedX + 2;

                    } else {
                        speedX = speedX - 2;
                    }

                }
                Granada *granadaDisparo = new Granada(15, 15, speedX, speedY, 60);
                granadaDisparo->setPosition(morteroX, morteroY);
                granadaDisparo->loadSprite(TEX2, 0, 0);
                granadaDisparo->spriteMortero();
                CARGADORGRANADA.push_back(granadaDisparo);
                RelojGranada.restart();

            }
        }

    } else if (tipo == 4) {//vaca
        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
        actual = 1;
        if (abs(dif) > 320 || pasota || abs(dify) > 200) {
            hitBoxataqueVaca.setScale(0, 0);
            //Movimiento random
            velocidadAnimacion = 0.1;
            velocidadmovimiento = 600.0f;
            if (RelojRandom.getElapsedTime().asMilliseconds() > 1000 && pasota) {
                pasota = false;
                RelojRandom.restart();
            }
            if (c->getElapsedTime().asMilliseconds() > 1000) {
                if (time_aux == -1 || time1 == time_aux) {
                    random = rand() % 2;
                    time_aux = time1 + 1;
                }
            }
            if (random == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
                animacion->orientacion(0);
                if (!muro) {
                    movimiento.x = tiempo*velocidadmovimiento;
                } else {
                    movimiento.x = 0;
                }
            }

            if (random == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
                animacion->orientacion(1);
                if (!muro) {
                    movimiento.x = -tiempo*velocidadmovimiento;
                } else {
                    movimiento.x = 0;
                }
            }

        } else {

            time_aux = time1;
            if (abs(dif) > 80 && abs(dify) < 200) {
                //Movimiento a jugador


                if (RelojRandom.getElapsedTime().asMilliseconds() > 1000) {
                    random2 = rand() % 100;
                    RelojRandom.restart();
                }
                if (random2 >= 10) {
                    //Movimiento a jugador
                    pasota = false;
                    time_aux = time1;
                    velocidadAnimacion = 0.02;
                    velocidadmovimiento = 2100.0f;
                    if (posJugador.x < posEnemigo.x) {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(1);

                        if (!muro) {
                            movimiento.x = -tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                        actual = 1;
                        animacion->orientacion(0);

                        if (!muro) {
                            movimiento.x = tiempo*velocidadmovimiento;
                        } else {
                            movimiento.x = 0;
                        }
                    }
                } else {
                    pasota = true;
                }

            } else {
                //atacar        
                sonidoAtaque->setReproduccion(0);//seteamos la reproduccion para que se pueda escuchar el sonido

                if (abs(dify) < 100) {
                    velocidadAnimacion = 0.02;
                    velocidadmovimiento = 2000.0f;
                    if (posJugador.x < posEnemigo.x) {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
                        actual = 0;
                        animacion->orientacion(1);
                        //sonidoAtaque->reproducir();
                    } else {
                        totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
                        actual = 0;
                        animacion->orientacion(0);
                        //sonidoAtaque->reproducir();
                    }
                    if (getframeActual(tiempoanimacion) == 10) {

                        hitBoxataqueVaca.setScale(7, 4);
                    } else {
                        hitBoxataqueVaca.setScale(0, 0);
                    }
                }
            }
        }
    }
    animacion->Movimiento(movimiento);
}

void Enemigo::Saltar() {




    if (muro && suelo) {
        velocidad.y = -velocidadsalto;

    } else if (!suelo) {

        velocidad.y += gravedad;

    } else {
        animacion->MovimientoInterpolado(Vector2f(getPos().x, distanciasuelo));
        velocidad.y = 0;

    }
    if (!colision) {
        suelo = false;
    }
    animacion->Movimiento(velocidad);

    /*
    if ((posicion.y + 2) != distanciasuelo) {
        if (arma==0){
            totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
            actual = 3;
        }else if (arma==1){
            totalSpritesAnimacion = animacion->getNumAnimaciones()[17];
            actual = 17;
        }
    }
     */


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
    for (contador = 0; contador < CARGADORGRANADA.size(); contador++) {//granadas
   
        window.draw(CARGADORGRANADA[contador]->getSprite());
    }
}

Vector2f Enemigo::getPos() {
    return animacion->getSpriteE().getPosition();
}

int Enemigo::getActual() {

    return actual;
}

int Enemigo::getframeActual(Time& tiempo) {

    int frameActual = static_cast<int> ((tiempo.asSeconds() / velocidadAnimacion) * 3) % totalSpritesAnimacion;

    return frameActual;

}

int Enemigo::getVidas() {
    return vidas;
}

void Enemigo::restarVidas() {
    if (vidas > 0)
        vidas--;
}

void Enemigo::update(Time &tiempo, Time &tiempoanimacion, Jugador jugador) {


    *viejo = *nuevo;
    Movimiento(tiempo, tiempoanimacion, jugador);
    Saltar();
    //Disparar();
    UpdateGranada();
    //DispararGranada();
    nuevo->actualizartiempo(getPos().x, getPos().y);

}

void Enemigo::render(float interpolacion, Time &tiempo) {
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& Window = motor->getWindow();


    actualizarHitBoxataqueVaca();
    actualizarHitbox();

    animacion->MovimientoInterpolado(viejo->getInterpolacion(viejo, nuevo, interpolacion));
    if(tipo == 3 && getframeActual(tiempo)==11){//para reproducion de sonido de tipo mortero, solo lo hara cuando llegue al frame 11
        if(sonidoAtaque->getReproduccion()==0){
            
        sonidoAtaque->reproducir();
        sonidoAtaque->setReproduccion(1);
        }
    }
    if(tipo == 4 && getframeActual(tiempo)==8){//para reproducion de sonido de vaca, solo lo hara cuando llegue al frame 8
        if(sonidoAtaque->getReproduccion()==0){
            
        sonidoAtaque->reproducir();
        sonidoAtaque->setReproduccion(1);
        }
    }
    Window.draw(animacion->getSprite(actual, getframeActual(tiempo)));

    RenderGranada(Window);

    //Window.draw(hitBoxataqueVaca);
    //Window.draw(hitBox);

}

void Enemigo::actualizarHitbox() {

    if (tipo == 4) {

        hitBox.setScale(1.5, 3.7);
        hitBox.setPosition(getPos().x - 25, getPos().y - 115);

    } else if (tipo == 2 || tipo == 1) {

        hitBox.setScale(1.5, 2.2);
        hitBox.setPosition(getPos().x - 25, getPos().y - 70);

    } else if (tipo == 3) {
        hitBox.setScale(1.5, 1.5);
        hitBox.setPosition(getPos().x - 25, getPos().y - 60);
    }

}

void Enemigo::actualizarHitBoxataqueVaca() {

    if (tipo == 4) {
        if (animacion->getOrientacion() == 1)
            hitBoxataqueVaca.setPosition(getPos().x - 80, getPos().y - 50);
        if (animacion->getOrientacion() == 0)
            hitBoxataqueVaca.setPosition(getPos().x + 10, getPos().y - 50);

    }
}

RectangleShape Enemigo::gethitBox() {

    return hitBox;
}

void Enemigo::calcularColision(FloatRect** arrayColisiones, int nobjetos) {



    bool colSuelo = false;
    bool colMuro = false;
    for (int i = 0; i < nobjetos - 2; i++) {
        FloatRect* a = arrayColisiones[i];

        if (a->intersects(hitBox.getGlobalBounds())) {


            //cout << "posicion a " << a->top << " PJ " << hitBox.getGlobalBounds().top << endl;
            colision = true;

            if (a->left >= hitBox.getGlobalBounds().left + hitBox.getGlobalBounds().width - 15) {

                //cout<<"no pasas"<<endl;
                //cout << "posicion a " << a->top << " PJ " << hitBox.getGlobalBounds().top << endl;
                colMuro = true;
                muro = true;
                if (random == 0) {
                    muro = false;
                    //cout << "murito---->" << muro << endl;
                }

            } else if (a->left + a->width - 15 <= hitBox.getGlobalBounds().left) {
                // cout << "no pasas" << endl;
                muro = true;
                colMuro = true;
                if (random == 1) {
                    muro = false;
                    //   cout << "murito---->" << muro << endl;
                }
            }

            if (a->top >= hitBox.getGlobalBounds().top) {
                colSuelo = true;
                suelo = true;
                if (!muro) {
                    if (tipo == 3 || tipo == 2) {
                        distanciasuelo = a->top + 14;
                    } else if (tipo == 4 || tipo == 1) {
                        distanciasuelo = a->top + 4;
                    }
                }
            }


        } else {
            colision = false;
        }
        for (int contador = 0; contador < CARGADORGRANADA.size(); contador++) {
           
            CARGADORGRANADA[contador]->explota(arrayColisiones[i]);
        }
        //cout << "el suelo es:" << suelo << endl;
        //cout << "i: " << i << " => " << a->left << ", " << a->top << " [" << a->width << ", " << a->height << "]" << endl;
    }

    if (!colSuelo) {
        suelo = false;
    }
    if (!colMuro) {
        muro = false;
    }

}

void Enemigo::ColisionJugador(Jugador &jugador) {
    bool golpeado = false;
    if (tipo == 4) {
        if (jugador.gethitBox().getGlobalBounds().intersects(hitBoxataqueVaca.getGlobalBounds())) {
            if (RelojCuchillo.getElapsedTime().asSeconds() > 0.1) {
                jugador.restarVidas();
                RelojCuchillo.restart();
                cout << "ostiaputacomo pegan" << endl;
            }
        }
    }
    //cuchillo
    if (jugador.gethitBox().getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
        jugador.animacionCuchillo(true);
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (RelojCuchillo.getElapsedTime().asSeconds() > 3) {
                restarVidas();
                cout << "numero de vidas" << getVidas() << endl;
                RelojCuchillo.restart();
            }

        }
    } else {
        jugador.animacionCuchillo(false);
    }

    //balas
    if (!golpeado) {
        for (int i = 0; i < jugador.getArrayBalas().size(); i++) {

            if (jugador.getArrayBalas()[i]->getSprite().getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
                restarVidas();
                golpeado = true;
                cout << "numero de vidas" << getVidas() << endl;
            }
        }
    }
    //granadas
    for (int j = 0; j < jugador.getArrayGranadas().size(); j++) {

        if (jugador.getArrayGranadas()[j]->getSprite().getGlobalBounds().intersects(hitBox.getGlobalBounds())) {
            restarVidas();

        }
    }


}