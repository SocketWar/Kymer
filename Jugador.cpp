
#include "Jugador.h"
#include "Estado.h"
#include "Bala.h"
#include "Granada.h"

Jugador::Jugador(int anchura, int altura) {

    gravedad = 2.0f;
    distanciasuelo = 458;
    velocidadsalto = 20.0f;
    velocidad.x = 0;
    velocidad.y = 0;

    velocidadanimacion = 0.1;
    velocidadmovimiento = 900.0f;

    //Sprites
    animacion = new Animacion("res/img/PersonajeFull.png");
    animacion->spritePersonaje('p');
    velocidadAnimacion = 0.1;
    countBala = 0;

    //Estados
    viejo = new Estado();
    nuevo = new Estado();

    if (!TEX.loadFromFile("res/img/balada2.png")) {
        std::cerr << "Error en textura bala";
        exit(0);
    }
    if (!TEX2.loadFromFile("res/img/SpriteGranada.png")) {
        std::cerr << "Error en textura Granada";
        exit(0);
    }
}

void Jugador::Movimiento(Time &time) {

    float tiempo = time.asSeconds();
    Vector2f movimiento(0.0f, 0.0f);
    actual = 0;
    totalSpritesAnimacion = animacion->getNumAnimaciones()[0];

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
        actual = 1;
        animacion->orientacion(1);
        movimiento.x = tiempo*velocidadmovimiento;
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[1];
        actual = 1;
        animacion->orientacion(0);
        movimiento.x = -tiempo*velocidadmovimiento;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        totalSpritesAnimacion = animacion->getNumAnimaciones()[2];
        actual = 2;
    }

    animacion->Movimiento(movimiento);
}

void Jugador::Saltar() {

    Vector2f posicion = getPos();
    //cout<<posicion.y<<endl;
    velocidadAnimacion = 0.3;
    if (Keyboard::isKeyPressed(Keyboard::Space) && (posicion.y + 2) == distanciasuelo) {
        velocidad.y = -velocidadsalto;

    }
    if ((posicion.y + 2) != distanciasuelo) {

        totalSpritesAnimacion = animacion->getNumAnimaciones()[3];
        actual = 3;
    }

    if (posicion.y + animacion->getSpriteE().getScale().y < distanciasuelo || velocidad.y < 0) {

        velocidad.y += gravedad;

    } else {

        animacion->MovimientoInterpolado(Vector2f(posicion.x, distanciasuelo - animacion->getSpriteE().getScale().y));
        velocidad.y = 0;

    }

    animacion->Movimiento(velocidad);
}

void Jugador::Disparar() {
    velocidadAnimacion = 0.1;
    int speedX = 0;
    int speedY = 0;
    float balaX = 0;
    float balaY = 0;

    if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::A)) {
        velocidadAnimacion = 0.085;
        if (RelojBala.getElapsedTime().asMilliseconds() > 500) {
            speedY = -25;
            speedX = 0;
            balaX = animacion->getSpriteE().getPosition().x - 20;
            balaY = animacion->getSpriteE().getPosition().y + 10;
            Bala *balaDisparo = new Bala(9, 23, speedX, speedY, 50);
            balaDisparo->setPosition(balaX, balaY);
            balaDisparo->loadSprite(TEX, 0, 0);
            CARGADOR.push_back(balaDisparo);
            RelojBala.restart();
        }
        totalSpritesAnimacion = animacion->getNumAnimaciones()[7];
        actual = 7;
    } else if (Keyboard::isKeyPressed(Keyboard::A)) {
        velocidadAnimacion = 0.085;
        if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::Right) && distanciasuelo == (getPos().y + 2)) {

            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
            actual = 8;


        } else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::Left) && distanciasuelo == (getPos().y + 2)) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[8];
            actual = 8;

        } else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::Down) && distanciasuelo == (getPos().y + 2)) {

            totalSpritesAnimacion = animacion->getNumAnimaciones()[6];
            actual = 6;

        } else {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[5];
            actual = 5;
        }
        if (RelojBala.getElapsedTime().asMilliseconds() > 500) {
            if (animacion->getOrientacion() != 0) {
                speedX = 25;
                speedY = 0;
                balaX = animacion->getSpriteE().getPosition().x + 50;
                balaY = animacion->getSpriteE().getPosition().y + 100;
            } else {
                speedX = -25;
                speedY = 0;
                balaX = animacion->getSpriteE().getPosition().x - 50;
                balaY = animacion->getSpriteE().getPosition().y + 100;
            }
            Bala *balaDisparo = new Bala(9, 23, speedX, speedY, 50);
            balaDisparo->setPosition(balaX, balaY);
            balaDisparo->loadSprite(TEX, 0, 0);
            CARGADOR.push_back(balaDisparo);
            RelojBala.restart();
        }

    }



}

void Jugador::DispararGranada() {
    velocidadAnimacion = 0.1;
    int speedX = 0;
    int speedY = 0;
    float GranadaX = 0;
    float GranadaY = 0;

    if (Keyboard::isKeyPressed(Keyboard::G)) {
        velocidadAnimacion = 0.1;

        if (Keyboard::isKeyPressed(Keyboard::G) && Keyboard::isKeyPressed(Keyboard::Right) && distanciasuelo == (getPos().y + 4)) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[12];
            actual = 12;

        } else if (Keyboard::isKeyPressed(Keyboard::G) && Keyboard::isKeyPressed(Keyboard::Left) && distanciasuelo == (getPos().y + 4)) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[12];
            actual = 12;

        } else if (Keyboard::isKeyPressed(Keyboard::G) && Keyboard::isKeyPressed(Keyboard::Down) && distanciasuelo == (getPos().y + 4)) {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[13];
            actual = 13;
        } else {
            totalSpritesAnimacion = animacion->getNumAnimaciones()[11];
            actual = 11;
        }

        if (RelojGranada.getElapsedTime().asMilliseconds() > 600) {
            if (animacion->getOrientacion() != 0) {
                speedX = 10;
                speedY = 15;
                GranadaX = animacion->getSpriteE().getPosition().x + 40;
                GranadaY = animacion->getSpriteE().getPosition().y + 100;
            } else {
                speedX = -10;
                speedY = 15;
                GranadaX = animacion->getSpriteE().getPosition().x;
                GranadaY = animacion->getSpriteE().getPosition().y + 100;
            }
            Granada *granadaDisparo = new Granada(18, 11, speedX, speedY, 60);
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

void Jugador::RenderDisparo(RenderWindow &window) {
    int contador = 0;
    for (contador = 0; contador < CARGADOR.size(); contador++) {
        window.draw(CARGADOR[contador]->getSprite());
    }
    for (contador = 0; contador < CARGADORGRANADA.size(); contador++) {
        window.draw(CARGADORGRANADA[contador]->getSprite());
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
    vidas = i;
}

int Jugador::getVidas() {
    return vidas;
}

void Jugador::actualizarEstado() {

    viejo = nuevo;

}

void Jugador::setEstado() {

    nuevo->actualizartiempo(getPos().x, getPos().y);

}

Estado* Jugador::getViejo() {


    return viejo;
}

Estado* Jugador::getNuevo() {

    return nuevo;
}