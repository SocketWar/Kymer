

#include "MovimientoIA.h"

MovimientoIA::MovimientoIA() {
}



void MovimientoIA::movimentoIA(Time& tiempo, RectangleShape& cuadrado, RectangleShape& cuadradoIA){
    
    float posicionxC=cuadrado.getPosition().x;
    float posicionyC=cuadrado.getPosition().y;
    
    float posicionxIA=cuadradoIA.getPosition().x;
    float posicionyIA=cuadradoIA.getPosition().y;
    
    
    if(posicionxC!= posicionxIA){
        
        /*
        if(posicionyC>posicionyIA){
            
           cuadradoIA.move(0,tiempo.asSeconds()*100);
           
        }else if(posicionyC<posicionyIA){
            
            cuadradoIA.move(0,-tiempo.asSeconds()*100);
        }
         */
        
       
        if(posicionxC>posicionxIA){
            
            cuadradoIA.move(tiempo.asSeconds()*300,0);
            
        }else if(posicionxC<posicionxIA){
            
            cuadradoIA.move(-tiempo.asSeconds()*300,0);
            
        }
        
        
        
    }
    
}

void MovimientoIA::esquivarIA(Time& tiempo, CircleShape& circulo, RectangleShape& cuadradoIA){
    
    
    float circulox= circulo.getPosition().x;
    float circuloy= circulo.getPosition().y;
    
    float posicionxIA=cuadradoIA.getPosition().x;
    float posicionyIA=cuadradoIA.getPosition().y;
    
    float altoIA = cuadradoIA.getLocalBounds().height;
    float anchoIA = cuadradoIA.getLocalBounds().width;
    
   // cout<<"posicion x circulo------>"<<circulox<<endl;
    //cout<<"posicion alto cuadrado----->"<<posicionyIA<<endl;
   // 
    
    
    
   if(circuloy<=altoIA+posicionyIA && circuloy>=posicionyIA-altoIA && circulox>anchoIA+posicionxIA-100){
       
        cuadradoIA.move(0,-tiempo.asSeconds()*200);
        
   } 
    
  
}
