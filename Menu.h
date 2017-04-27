#include <iostream>

#include "cabecera.hpp"

const int elementos=3;

class Menu {
public:
    Menu(int anchura,int altura);
    void dibujar(RenderWindow &w);
    void MoverArriba();
    void MoverAbajo();
    void seleccion(int &menu,RenderWindow &w);
    void SetText(RenderWindow &w,int menu);
    void SetPos(RenderWindow &w);
    
private:
    

    int indice;
    Font fuente;
    Text texto[elementos];
};



