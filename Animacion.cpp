
#include "Animacion.h"

Animacion::Animacion(string texto) {

    ORIENTACION = 1;
    tex = new Texture(); //reserva de memoria
    if (!tex->loadFromFile(texto)) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    tex->setSmooth(false);

}

//personaje 

void Animacion::spritePersonaje(char l) {

    int xi = 0;
    int yi = 0;
    int posX = 0;
    int posY = 0;

    switch (l) {

        case 'p':
            totalFotogramas = 29;
            animacion = new int [totalFotogramas];
            animacion[0] = 4; //parado
            animacion[1] = 6; //correr
            animacion[2] = 6; //agachado
            animacion[3] = 1; //saltoquieto
            animacion[4] = 6; //salto movimiento
            animacion[5] = 4; //disparo
            animacion[6] = 3; //disparo agachado
            animacion[7] = 4; //disparo arriba
            animacion[8] = 6; //disparo correr
            animacion[9] = 6; //cuchillo correr
            animacion[10] = 4; //cuchillo agachado
            animacion[11] = 3; //lanzar granada
            animacion[12] = 6; //lanzar granada corriendo
            animacion[13] = 4; //lanzar granada agachado
            animacion[14] = 4; //escopeta quieto
            animacion[15] = 6; //escopeta correr
            animacion[16] = 4; //escopeta agachado
            animacion[17] = 1; //escopeta salto
            animacion[18] = 2; //escopeta disparo quieto
            animacion[19] = 2; //escopeta disparo agachado
            animacion[20] = 2; //escopeta disparo arriba
            animacion[21] = 6; //escopeta disparo correr
            animacion[22] = 3; //escopeta lanzar granada quieto
            animacion[23] = 6; //escopeta lanzar granada corriendo
            animacion[24] = 4; //escopeta lanzar granada agachado
            animacion[25] = 6; //escopeta cuchillo correr
            animacion[26] = 4; //escopeta cuchillo agachado
            animacion[27] = 5; //MUERTO
            animacion[28] = 3; //VICTORIA
            xi = 54;
            yi = 77;
            posX = 150;
            posY = 50;
            escala = 2.f;
            break;
        case 'e':
            totalFotogramas = 27;
            animacion = new int [totalFotogramas];

            animacion[0] = 4; //alerta
            animacion[1] = 12; //correr
            animacion[2] = 4; //reirse
            animacion[3] = 3; //morir
            animacion[4] = 14; //tio lanza granadas
            animacion[5] = 8; //carga escopeta
            animacion[6] = 3; //disparo escopeta
            animacion[7] = 7; //morir acuchillado
            animacion[8] = 18; //mortero
            animacion[9] = 6; //cuchillo correr
            animacion[10] = 4; //cuchillo agachado
            animacion[11] = 3; //lanzar granada
            animacion[12] = 6; //lanzar granada corriendo
            animacion[13] = 4; //lanzar granada agachado
            animacion[14] = 4; //escopeta quieto
            animacion[15] = 6; //escopeta correr
            animacion[16] = 4; //escopeta agachado
            animacion[17] = 1; //escopeta salto
            animacion[18] = 2; //escopeta disparo quieto
            animacion[19] = 2; //escopeta disparo agachado
            animacion[20] = 2; //escopeta disparo arriba
            animacion[21] = 6; //escopeta disparo correr
            animacion[22] = 3; //escopeta lanzar granada quieto
            animacion[23] = 6; //escopeta lanzar granada corriendo
            animacion[24] = 4; //escopeta lanzar granada agachado
            animacion[25] = 6; //escopeta cuchillo correr
            animacion[26] = 4; //escopeta cuchillo agachado
            posX = 275;
            posY = 505;
            escala = 2.2f;

            xi = 60;
            yi = 50;

            break;
        case 'v':
                tex->setSmooth(true);
            totalFotogramas = 27;
            animacion = new int [totalFotogramas];

            animacion[0] = 17 ;//alerta
            animacion[1] = 8; //correr
            animacion[2] = 4; //reirse
            animacion[3] = 3; //morir
            animacion[4] = 14; //tio lanza granadas
            animacion[5] = 8; //carga escopeta
            animacion[6] = 3; //disparo escopeta
            animacion[7] = 7; //morir acuchillado
            animacion[8] = 18; //mortero
            animacion[9] = 6; //cuchillo correr
            animacion[10] = 4; //cuchillo agachado
            animacion[11] = 3; //lanzar granada
            animacion[12] = 6; //lanzar granada corriendo
            animacion[13] = 4; //lanzar granada agachado
            animacion[14] = 4; //escopeta quieto
            animacion[15] = 6; //escopeta correr
            animacion[16] = 4; //escopeta agachado
            animacion[17] = 1; //escopeta salto
            animacion[18] = 2; //escopeta disparo quieto
            animacion[19] = 2; //escopeta disparo agachado
            animacion[20] = 2; //escopeta disparo arriba
            animacion[21] = 6; //escopeta disparo correr
            animacion[22] = 3; //escopeta lanzar granada quieto
            animacion[23] = 6; //escopeta lanzar granada corriendo
            animacion[24] = 4; //escopeta lanzar granada agachado
            animacion[25] = 6; //escopeta cuchillo correr
            animacion[26] = 4; //escopeta cuchillo agachado
            posX = 550;
            posY = 425;
            escala = 2.2f;
                
            xi = 123;
            yi = 87;
            break;
    }

    sprites = new Sprite**[totalFotogramas];
    for (int l = 0; l < totalFotogramas; l++) {
        sprites[l] = new Sprite*[totalFotogramas];
        //cout<<"he entrado "<<endl;
    }

    for (int f = 0; f < totalFotogramas; f++) {
        //cout<<"he entrado "<<f<<endl;

        for (int j = 0; j < animacion[f]; j++) {
            sprites[f][j] = new sf::Sprite(*tex);
            sprites[f][j]->setScale(escala, escala);
            sprites[f][j]->setTextureRect(IntRect(xi * j, yi * f, xi, yi));
            sprites[f][j]->setPosition(posX, posY);
            sprites[f][j]->setOrigin(sprites[f][j]->getLocalBounds().width / 2, sprites[f][j]->getLocalBounds().height / 2);
            sprites[f][j]->setOrigin(15, 0);

        }
    }
    if (!sprites) {
        cout << "no se ha podido reservar" << endl;
    }

}

int* Animacion::getNumAnimaciones() {
    return animacion;
}

Sprite Animacion::getSprite(int animacion, int pos) {

    return *sprites[animacion][pos];
}

Sprite Animacion::getSpriteE() {

    return ***sprites;
}

void Animacion::orientacion(int orientacion) {
    int escalado = 0;
    ORIENTACION = orientacion;
    if (orientacion == 0) {//miramos a la izq
        escalado = -escala;
    } else {
        escalado = escala;
    }
    for (int f = 0; f < totalFotogramas; f++) {
        for (int j = 0; j < animacion[f]; j++) {
            sprites[f][j]->setScale(escalado, escala);
            //sprites[f][j]->setPosition(150,50);
        }
    }
}

void Animacion::Movimiento(Vector2f vector) {

    for (int f = 0; f < totalFotogramas; f++) {
        for (int j = 0; j < animacion[f]; j++) {
            sprites[f][j]->move(vector);
        }
    }
}

void Animacion::MovimientoInterpolado(Vector2f vector) {

    for (int f = 0; f < totalFotogramas; f++) {
        for (int j = 0; j < animacion[f]; j++) {
            sprites[f][j]->setPosition(vector.x, vector.y);
        }
    }

}



