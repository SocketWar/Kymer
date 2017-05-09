

#include "Enemigo.h"

Enemigo::Enemigo() {
    
    
    animacion = new Animacion("res/img/enemigocomun1.png");
    animacion->spritePersonaje('e');
    cout<<"hola"<<endl;
}

Enemigo::Enemigo(const Enemigo& orig) {
}

Enemigo::~Enemigo() {
}



Animacion Enemigo::getAnimacion(){
    
    return *animacion;
    
}