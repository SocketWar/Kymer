#include<string.h>

#include "Menu.h"

Menu::Menu(int anchura,int altura) {
    
    
        if(!fuente.loadFromFile("comic.ttf")){
       cout<< "Error al cargar la fuente"<<endl;
    }else{
        
     texto[0].setFont(fuente);
     texto[0].setString("Inicio");
     texto[0].setColor(Color::White);
     
     texto[1].setFont(fuente);
     texto[1].setString("Resolucion");
     texto[1].setColor(Color::Red);
     
     texto[2].setFont(fuente);
     texto[2].setString("Ayuda");
     texto[2].setColor(Color::Red);
     
     
     
     texto[0].setPosition( anchura/2, altura/ (elementos+1) * 1);
     texto[1].setPosition( anchura/2, altura/ (elementos+1) * 2);
     texto[2].setPosition( anchura/2, altura/ (elementos+1) * 3);    
 
    }
     indice=0;
     
    }
    

void Menu::dibujar(RenderWindow& w){
    
    
    for(int i=0;i<elementos;i++){
        
     w.draw(texto[i]);
     
    }
    
}
    void Menu::MoverAbajo(){
        
     if((indice+1) < elementos){
        texto[indice].setColor(Color::Red);
        indice++;
        texto[indice].setColor(Color::White);
         
     }   
        
    }
    
    void Menu::MoverArriba(){
     
        if(indice-1 >=0){
        texto[indice].setColor(Color::Red);
        indice--;
        texto[indice].setColor(Color::White);
         
     }
        
        
    }
    
    
    
    void Menu::seleccion(int& menu,RenderWindow& w){
        
        bool encontrado = false;
        for(int i;i<elementos && encontrado==false;i++){
            if(texto[i].getColor()==Color::White){
            if(texto[i].getString()=="Resolucion"){
                menu=1;
                encontrado=true;
                }else if(texto[i].getString()=="Inicio"){
                menu=0;
                encontrado=true;    
                }else if(texto[i].getString()=="Ayuda"){
                menu=2;
                encontrado=true;    
                }else if(texto[i].getString()=="800x600"){
                   
                    w.setSize(Vector2u(800,600));
                    SetPos(w);
                    encontrado=true;   
                }else if(texto[i].getString()=="1024x720"){
                    
                    w.setSize(Vector2u(1024,720));
                    SetPos(w);
                    encontrado=true;   
                }else if(texto[i].getString()=="1920x1080"){
                    
                    w.setSize(Vector2u(1920,1080));
                    SetPos(w);
                    encontrado=true;   
                }
                
            }
        }
       
    }
    
    void Menu::SetText(RenderWindow &w,int menu){
        
        
        switch(menu){
           
            case 1:
                texto[0].setString("800x600");
                texto[1].setString("1024x720");
                texto[2].setString("1920x1080");
                break;
                
            case 0:
                texto[0].setString("Inicio");
                texto[1].setString("Resolucion");
                texto[2].setString("Ayuda");
                break;
        }
        
        
        dibujar(w);
    }
    

    void Menu::SetPos(RenderWindow& w){
        cout<< w.getSize().x << "x" << w.getSize().y<< endl;
         texto[0].setPosition( w.getSize().x/2,  w.getSize().y/ (elementos+1) * 1);
         texto[1].setPosition( w.getSize().x/2,  w.getSize().y/ (elementos+1) * 2);
         texto[2].setPosition( w.getSize().x/2,  w.getSize().y/ (elementos+1) * 3);   
        
         dibujar(w);
        
    }

