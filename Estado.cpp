

#include "Estado.h"

Estado::Estado(float x,float y) {
    
    posx=x;
    posy=y;
    
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





