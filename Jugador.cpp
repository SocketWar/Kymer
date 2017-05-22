
#include "Jugador.h"

Jugador::Jugador(int anchura, int altura,float posx,float posy) {
    disparo = new sonido();
    disparo->setSonido("res/audio/shot.wav");
    disparo->getSonido().setLoop(false);
    
    cuchillaco = new sonido();
    cuchillaco->setSonido("res/audio/cuchillo.wav");
    cuchillaco->getSonido().setLoop(false);
    
    lanzallamas = new sonido();
    lanzallamas->setSonido("res/audio/faia.wav");
    lanzallamas->getSonido().setLoop(false);
    
   
    muerto = 0;
    muerte = new sonido();
    muerte->setSonido("res/audio/dead.wav");
    muerte->getSonido().setLoop(false);
    
    arma = 0;
    numEscopeta = 0;
    vidas = 5;
    punt=0;
    granadas = 100;
    gravedad = 2.0f;
    distanciasuelo = 700;
    velocidadsalto = 20.0f;
    velocidad.x = 0;
    velocidad.y = 0;

    velocidadanimacion = 0.1;
    velocidadmovimiento = 2000.0f;

    //Sprites
    animacion = new Animacion("res/img/Personaje13052017.png",posx,posy);
    animacion->spritePersonaje('p');
    velocidadAnimacion = 0.1;
    countBala = 0;

    //Estados
    viejo = new Estado();
    nuevo = new Estado();
    //Colisiones
    hitBox = new RectangleShape();
    hitBox->setScale(1.5, 2.2);
    hitBox->setSize(Vector2f(32, 32));
    hitBox->setFillColor(Color::Blue);
    muro = false;
    cuchillo = false;
    if (!TEX.loadFromFile("res/img/balada2.png")) {
        std::cerr << "Error en textura bala";
        exit(0);
    }
    if (!TEX2.loadFromFile("res/img/SpriteGranada.png")) {
        std::cerr << "Error en textura Granada";
        exit(0);
    }
    if (!TEX3.loadFromFile("res/img/escopeta.png")) {
        std::cerr << "Error en textura Granada";
        exit(0);
    }


}

void Jugador::Movimiento(Time &time) {

    float tiempo = time.asSeconds();
    Vector2f movimiento(0.0f, 0.0f);

    if (vidas <= 0) {
        Morir();

    } else if (Keyboard::isKeyPressed(Keyboard::V) || Joystick::isButtonPressed(0,1)) {
        velocidadAnimacion = 0.1f;
        totalSpritesAnimacion = animacion->getNumAnimaciones()[28];
        actual = 28;
    } else {
        if (arma == 0) {
            actual = 0;


            totalSpritesAnimacion = animacion->getNumAnimaciones()[0];
        } else if (arma == 1) {
            actual = 14;
            totalSpritesAnimacion = animacion->getNumAnimaciones()[14];
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Joystick::isButtonPressed(0,12)) {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[15];
                actual = 15;
            }
            animacion->orientacion(1);
            if (!muro) {
                movimiento.x = tiempo*velocidadmovimiento;
            } else {
                movimiento.x = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) || Joystick::isButtonPressed(0,11)) {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
                actual = 1;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[15];
                actual = 15;
            }
            animacion->orientacion(0);
            if (!muro) {
                movimiento.x = -tiempo*velocidadmovimiento;
            } else {
                movimiento.x = 0;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0,14)) {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[2];
                actual = 2;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[16];
                actual = 16;
            }
        }

        animacion->Movimiento(movimiento);
    }
}

void Jugador::Saltar() {


    //float posicion = animacion->getSpriteE().getGlobalBounds().top + animacion->getSpriteE().getGlobalBounds().height;
    //cout<<"posicion de los pies"<<posicion<<endl;
    velocidadAnimacion = 0.3;


    if (Keyboard::isKeyPressed(Keyboard::C) || Joystick::isButtonPressed(0,5)) {
        suelo = false;
    }

    if ((Keyboard::isKeyPressed(Keyboard::Space) || Joystick::isButtonPressed(0,0)) && suelo) {
        velocidad.y = -velocidadsalto;

    } else if (!suelo) {
        if (arma == 0) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
            actual = 3;
        } else {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[17];
            actual = 17;
        }
        velocidad.y += gravedad;
    } else {
        animacion->MovimientoInterpolado(Vector2f(getPos().x, distanciasuelo));
        velocidad.y = 0;

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
    if (!colision) {
        suelo = false;
    }

}


void Jugador::Disparar() {
    velocidadAnimacion = 0.1;
    float speedX = 0;
    float speedY = 0;
    float balaX = 0;
    float balaY = 0;
    //cout<< numEscopeta <<endl;
    if ((Keyboard::isKeyPressed(Keyboard::Up) || Joystick::isButtonPressed(0,13)) && (Keyboard::isKeyPressed(Keyboard::A) || Joystick::isButtonPressed(0,2))) {
        velocidadAnimacion = 0.085;
        if (arma == 0) {
            if (RelojBala.getElapsedTime().asMilliseconds() > 700) {
                speedY = -25;
                speedX = 0;
                balaX = animacion->getSpriteE().getPosition().x - 10;
                balaY = animacion->getSpriteE().getPosition().y - 90;
                Bala *balaDisparo = new Bala(9, 23, speedX, speedY, 50);
                balaDisparo->setPosition(balaX, balaY);
                balaDisparo->loadSprite(TEX, 0, 0);
                CARGADOR.push_back(balaDisparo);
                RelojBala.restart();
            }
        }else{
            if (RelojBala.getElapsedTime().asMilliseconds() > 100) {
                numEscopeta -= 1;
                speedY = -1;
                speedX = 0;
                balaX = animacion->getSpriteE().getPosition().x-20;
                balaY = animacion->getSpriteE().getPosition().y - 130;
                Bala *balaDisparo = new Bala(49, 96, speedX, speedY, 3);
                balaDisparo->setPosition(balaX, balaY);
                balaDisparo->loadSprite(TEX3, 0, 0);
                disparo->reproducir();
                CARGADOR.push_back(balaDisparo);
                RelojBala.restart();
                lanzallamas->reproducir();
                        
            }
            
        }
        if (arma == 0) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[7];
            actual = 7;
        } else if (arma == 1) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[20];
            actual = 20;
        }

    } else if (Keyboard::isKeyPressed(Keyboard::A) || Joystick::isButtonPressed(0,2)) {
        velocidadAnimacion = 0.085;

        if (cuchillo) {
            cuchillaco->reproducir();
            if (arma == 0) {
                if (Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0,14)) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[10];
                    actual = 10;
                } else {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[9];
                    actual = 9;
                }
            } else if (arma == 1) {
                if (Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0,14)) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[26];
                    actual = 26;
                } else {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[25];
                    actual = 25;
                }
            }

        }


        if (!cuchillo) {
            if(arma==1)
                velocidadAnimacion = 0.5;
                
            if (Keyboard::isKeyPressed(Keyboard::Right) || Joystick::isButtonPressed(0,12)) {

                if (arma == 0) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
                    actual = 8;
                    //            soundEffect->getSonido().play();
                } else if (arma == 1) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[21];
                    actual = 21;
                }
            } else if (Keyboard::isKeyPressed(Keyboard::Left) || Joystick::isButtonPressed(0,11)) {
                if (arma == 0) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
                    actual = 8;
                } else if (arma == 1) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[21];
                    actual = 21;
                }

            } else if (Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0,14)) {

                if (arma == 0) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
                    actual = 6;
                } else if (arma == 1) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[19];
                    actual = 19;
                }

            } else {

                if (arma == 0) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
                    actual = 5;
                } else if (arma == 1) {
                    totalSpritesAnimacion = animacion->getNumAnimaciones()[18];
                    actual = 18;
                }
            }
            if (arma == 0) {
                if (RelojBala.getElapsedTime().asMilliseconds() > 500) {
                    if (animacion->getOrientacion() != 0) {
                        speedX = 25;
                        speedY = 0;
                        balaX = animacion->getSpriteE().getPosition().x + 50;
                         if(Keyboard::isKeyPressed(Keyboard::Down)){
                             balaY = animacion->getSpriteE().getPosition().y - 40;
                        }else{
                            balaY = animacion->getSpriteE().getPosition().y - 60;
                        }
                    } else {
                        speedX = -25;
                        speedY = 0;
                        balaX = animacion->getSpriteE().getPosition().x - 50;
                         if(Keyboard::isKeyPressed(Keyboard::Down)){
                             balaY = animacion->getSpriteE().getPosition().y - 40;
                        }else{
                            balaY = animacion->getSpriteE().getPosition().y - 60;
                        }
                    }
                    Bala *balaDisparo = new Bala(9, 23, speedX, speedY, 50);
                    balaDisparo->setPosition(balaX, balaY);
                    balaDisparo->loadSprite(TEX, 0, 0);
                    CARGADOR.push_back(balaDisparo);
                        disparo->reproducir();
                 

                    RelojBala.restart();
                }
            } else {
                if (RelojBala.getElapsedTime().asMilliseconds() > 100) {
                    if (animacion->getOrientacion() != 0) {
                        speedX = 0.1f;
                        speedY = 0;
                        balaX = animacion->getSpriteE().getPosition().x + 50;
                        balaY = animacion->getSpriteE().getPosition().y - 70;
                    } else {
                        speedX = -0.1f;
                        speedY = 0;
                        balaX = animacion->getSpriteE().getPosition().x - 50;
                        balaY = animacion->getSpriteE().getPosition().y - 70;
                    }
                    Bala *balaDisparo = new Bala(49, 96, speedX, speedY, 3);
                    balaDisparo->setPosition(balaX, balaY);
                    balaDisparo->loadSprite(TEX3, 0, 0);
                    CARGADOR.push_back(balaDisparo);
                    numEscopeta -= 1;
                    RelojBala.restart();
               
                            lanzallamas->reproducir();
                        
                }
            }
        }
    }

}

void Jugador::DispararGranada() {
    velocidadAnimacion = 0.1;
    int speedX = 0;
    int speedY = 0;
    float GranadaX = 0;
    float GranadaY = 0;

    if ((Keyboard::isKeyPressed(Keyboard::G)||Joystick::isButtonPressed(0,3)) && granadas > 0) {
        velocidadAnimacion = 0.1;

        if ((Keyboard::isKeyPressed(Keyboard::G)||Joystick::isButtonPressed(0,3)) && (Keyboard::isKeyPressed(Keyboard::Right)||Joystick::isButtonPressed(0,12)) && distanciasuelo == (getPos().y + 4)) {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[12];
                actual = 12;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[23];
                actual = 23;
            }

        } else if ((Keyboard::isKeyPressed(Keyboard::G)||Joystick::isButtonPressed(0,3)) && (Keyboard::isKeyPressed(Keyboard::Left)||Joystick::isButtonPressed(0,11)) && distanciasuelo == (getPos().y + 4)) {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[12];
                actual = 12;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[23];
                actual = 23;
            }

        } else if ((Keyboard::isKeyPressed(Keyboard::G)||Joystick::isButtonPressed(0,3)) && (Keyboard::isKeyPressed(Keyboard::Down)||Joystick::isButtonPressed(0,14)) && distanciasuelo == (getPos().y + 4)) {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[13];
                actual = 13;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[24];
                actual = 24;
            }
        } else {
            if (arma == 0) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[11];
                actual = 11;
            } else if (arma == 1) {
                totalSpritesAnimacion = animacion->getNumAnimaciones()[22];
                actual = 22;
            }
        }

        if (RelojGranada.getElapsedTime().asMilliseconds() > 600) {
            granadas--;

            if (animacion->getOrientacion() != 0) {
                speedX = 10;
                speedY = 15;
                GranadaX = animacion->getSpriteE().getPosition().x + 40;
                GranadaY = animacion->getSpriteE().getPosition().y - 60;
            } else {
                speedX = -10;
                speedY = 15;
                GranadaX = animacion->getSpriteE().getPosition().x;
                GranadaY = animacion->getSpriteE().getPosition().y - 60;
            }
            Granada *granadaDisparo = new Granada(18, 11, speedX, speedY, 60);
            //            Granada *granadaDisparo = new Granada(112, 55, speedX, speedY, 60);
            granadaDisparo->setPosition(GranadaX, GranadaY);
            granadaDisparo->loadSprite(TEX2, 0, 0);
            CARGADORGRANADA.push_back(granadaDisparo);
            RelojGranada.restart();
        }


    }



}

void Jugador::UpdateDisparo() {
    int contador = 0;
    int move;
    std::vector<Bala*> CargadorAux;
    std::vector<Granada*> CargadorAuxGranada;
    for (contador = 0; contador < CARGADOR.size(); contador++) {
        CARGADOR[contador]->actualizarEstado();
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

        CARGADOR[contador]->getNuevo()->actualizartiempo(CARGADOR[contador]->getSprite().getPosition().x, CARGADOR[contador]->getSprite().getPosition().y);

    }
    CARGADOR = CargadorAux;
    //cout<<"Balas: " << CARGADOR.size() << endl;
    for (contador = 0; contador < CARGADORGRANADA.size(); contador++) {
        CARGADORGRANADA[contador]->actualizarEstado();
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

void Jugador::RenderDisparo(float interpolacion) {

    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& Window = motor->getWindow();

    int contador = 0;
    for (contador = 0; contador < CARGADOR.size(); contador++) {
        CARGADOR[contador]->getSprite().setPosition(CARGADOR[contador]->getViejo()->getInterpolacion(CARGADOR[contador]->getViejo(), CARGADOR[contador]->getNuevo(), interpolacion));
        Window.draw(CARGADOR[contador]->getSprite());
    }
    for (contador = 0; contador < CARGADORGRANADA.size(); contador++) {
        //CARGADOR[contador]->setPosition(CARGADOR[contador]->getViejo()->getInterpolacion(CARGADOR[contador]->getViejo(),CARGADOR[contador]->getNuevo(),interpolacion));
        Window.draw(CARGADORGRANADA[contador]->getSprite());
    }
}

void Jugador::Morir() {
    //para probar la animacio0n se pone en un boton por defecto "M"
    velocidadAnimacion = 0.2f;
   if(muerto <4){
    muerte->reproducir();    
    totalSpritesAnimacion = animacion->getNumAnimaciones()[27];
    actual = 27;
    muerto++;
    }
}

Vector2f Jugador::getPos() {
    return animacion->getSpriteE().getPosition();
}

Animacion Jugador::getAnimacion() {

    return *animacion;

}

int Jugador::getActual() {

    return actual;
}

int Jugador::gettotalSpritesAnimacion() {

    return totalSpritesAnimacion;
}

int Jugador::getframeActual(Time& tiempo) {

    int frameActual = static_cast<int> ((tiempo.asSeconds() / velocidadAnimacion) * 3) % totalSpritesAnimacion;

    return frameActual;

}

void Jugador::setVidas(int i) {
    if (vidas>=0 && vidas<=6)
    vidas = i;
}

int Jugador::getVidas() {
    return vidas;
}
void Jugador::setPunt(int i) {
    if (punt<10000)
    punt = i;
}

int Jugador::getPunt() {
    return punt;
}
void Jugador::restarVidas() {
    if (vidas > 0)
        vidas--;
}

void Jugador::setGranadas(int i) {
     if (granadas<100)
    granadas = i;
     
}

int Jugador::getGranadas() {
    return granadas;
}


void Jugador::setArma(int i) {
    arma = i;
    if (arma == 1) {
        numEscopeta += 5;
    }
}

void Jugador::actualizarEstado() {

    viejo = nuevo;

}

void Jugador::setEstado() {

    nuevo->actualizartiempo(getPos().x, getPos().y);

}

void Jugador::animacionCuchillo(bool c) {

    cuchillo = c;

}

Estado* Jugador::getViejo() {


    return viejo;
}

Estado* Jugador::getNuevo() {

    return nuevo;
}

sonido Jugador::getSonido() {
    return *soundEffect;
}

void Jugador::actualizarHitbox() {


    if (Keyboard::isKeyPressed(Keyboard::Down) || Joystick::isButtonPressed(0,14)) {

        hitBox->setScale(1.5, 1.5);
        hitBox->setPosition(getPos().x - 25, getPos().y - 48);

    } else {

        hitBox->setScale(1.5, 2.2);
        hitBox->setPosition(getPos().x - 25, getPos().y - 70);

    }
}

RectangleShape Jugador::gethitBox() {

    return *hitBox;
}

vector<Bala*> Jugador::getArrayBalas() {


    return CARGADOR;
}

vector<Granada*> Jugador::getArrayGranadas() {


    return CARGADORGRANADA;
}

void Jugador::calcularColision(FloatRect** arrayColisiones, int nobjetos,FloatRect muerte) {


    /*
      trol.setScale(1.5, 2.2);
      trol.setSize(Vector2f(32, 32));
      trol.setFillColor(Color::Blue);
    
      trol2.setScale(1.5, 2.2);
      trol2.setSize(Vector2f(32, 32));
      trol2.setFillColor(Color::Green);
     */
    bool colSuelo = false;
    bool colMuro = false;
    
    if(muerte.intersects(hitBox->getGlobalBounds())){
        
        cout<<"GAMEOVER"<< endl;
        vidas=0;
    }
    
    for (int i = 0; i < nobjetos - 2; i++) {
        FloatRect* a = arrayColisiones[i];

        if (a->intersects(hitBox->getGlobalBounds())) {


            //cout << "posicion a " << a->top << " PJ " << hitBox.getGlobalBounds().top << endl;
            colision = true;

            if (a->left >= hitBox->getGlobalBounds().left + hitBox->getGlobalBounds().width - 20) {

                //cout << "colisionmuro" << endl;
                colMuro = true;
                muro = true;

                if ((Keyboard::isKeyPressed(Keyboard::Left) || Joystick::isButtonPressed(0,11)) || a->top > hitBox->getGlobalBounds().top) {
                    muro = false;
                    //  cout << "yanocolisiona---->" << muro << endl;
                }
            }


            if (a->left + a->width - 15 <= hitBox->getGlobalBounds().left) {

                //cout << "colisionmuro" << endl;
                colMuro = true;
                muro = true;

                if ((Keyboard::isKeyPressed(Keyboard::Right) || Joystick::isButtonPressed(0,12)) || a->top > hitBox->getGlobalBounds().top) {

                    muro = false;
                    // cout << "yanocolisiona---->" << muro << endl;
                }
            }

            if (a->top >= hitBox->getGlobalBounds().top) {
                colSuelo = true;
                suelo = true;

                if (!muro) {
                    distanciasuelo = a->top + 2;
                }
            }

            //cout<<"rectanguloWid----->>"<<a->top<<endl;
            //cout<<"rectanguloLeft----->>"<<a->left<<endl;
            //cout<<"JugadorWid----->>"<<hitBox.getGlobalBounds().top<<endl;
            //cout<<"JugadorLeft----->>"<<hitBox.getGlobalBounds().left<<endl;

        } else {
            colision = false;
        }

        //cout << "el suelo es:" << suelo << endl;
        //cout << "i: " << i << " => " << a->left << ", " << a->top << " [" << a->width << ", " << a->height << "]" << endl;
        for (int contador = 0; contador < CARGADORGRANADA.size(); contador++) {
            CARGADORGRANADA[contador]->explota(arrayColisiones[i]);
        }
        
        for (int contador = 0; contador < CARGADOR.size(); contador++) {
            if(a->intersects(CARGADOR[contador]->getSprite().getGlobalBounds())){
                
                CARGADOR[contador]->setDestruir();
            }
            
        }
    }

    if (!colSuelo) {
        suelo = false;
    }
    if (!colMuro) {
        muro = false;
    }

}

void Jugador::update(Time &tiempo) {


    *viejo = *nuevo;
    if(numEscopeta<=0){
        arma=0;
    }else{
        arma=1;
    }
    Movimiento(tiempo);
    Saltar();
    Disparar();
    UpdateDisparo();
    DispararGranada();
    nuevo->actualizartiempo(getPos().x, getPos().y);

}

void Jugador::render(float interpolacion, Time &tiempo, hud& h) {
    Motor2D *motor = Motor2D::GetInstance();
    RenderWindow& Window = motor->getWindow();
    actualizarHud(h);
    actualizarHitbox();
    animacion->MovimientoInterpolado(viejo->getInterpolacion(viejo, nuevo, interpolacion));
    if (muerto<4){
        
        Window.draw(animacion->getSprite(actual, getframeActual(tiempo)));
    }
    else {
        
        Window.draw(animacion->getSprite(27, muerto));
    }
    RenderDisparo(interpolacion);
    // Window.draw(hitBox);

}

void Jugador::recogeObjeto(objetos &obj) {
  int i=0;
  //cout<<"tipo de objeto :" <<obj.getTipo()<<endl;
    if (obj.getSprite().getGlobalBounds().intersects(this->hitBox->getGlobalBounds())) {
        if (obj.getTipo() == 0) {
            obj.reproducirSonido();
            this->setArma(1);
        }else if (obj.getTipo() == 1) {
          
            i=getVidas()+1;
            this->setVidas(i);
        }else if (obj.getTipo() == 2) {
           
            i=getPunt()+50;
            this->setPunt(i);
        }else if (obj.getTipo() == 3) {
           
            i=getGranadas()+1;
            this->setGranadas(i);
        }

    }
}

void Jugador::actualizarHud(hud& h) {

    if (this->arma == 1) {
        h.changeArma(1);
    } else {
        h.changeArma(0);
    }
    h.changeContHP(vidas);
    h.changeGranada(granadas);
    h.changePunt(punt);
}
