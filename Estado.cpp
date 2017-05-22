

#include "Estado.h"

Estado::Estado() {
    
    posx=0;
    posy=0;
    
}

void Estado::actualizartiempo(float posicionx,float posiciony){
    
    posx=posicionx;
    posy=posiciony;
    
}

float Estado::getx(){
    
    return posx;
}

float Estado::gety(){
    
    return posy;
}

Vector2f Estado::getInterpolacion(Estado* viejo, Estado* nuevo, float interpolacion){
    
    
    float movimientox = viejo->getx()*(1 - interpolacion) + nuevo->getx() * interpolacion;
    
    float movimientoy = viejo->gety()*(1 - interpolacion) + nuevo->gety() * interpolacion;
    
    Vector2f interpol(movimientox,movimientoy);
    
    return interpol;
}

