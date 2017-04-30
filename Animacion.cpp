
#include "Animacion.h"

Animacion::Animacion(string texto) {
    
    ORIENTACION=1;
     tex = new Texture(); //reserva de memoria
        if (!tex->loadFromFile(texto))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
        
        tex->setSmooth(false);
}


void Animacion::spritePersonaje(){
    
    
    totalFotogramas=8;
    animacion = new int [8]; 
    animacion[0]=4;//parado
    animacion[1]=6;//correr
    animacion[2]=6;//agachado
    animacion[3]=5;//saltoquieto
    animacion[4]=6;//salto movimiento
    animacion[5]=4;//disparo
    animacion[6]=3;//disparo agachado
    animacion[7]=4;//disparo arriba
    sprites = new Sprite**[totalFotogramas];
   
    for (int l = 0; l<totalFotogramas; l++){
        sprites[l] = new Sprite*[totalFotogramas];
        cout<<"he entrado "<<endl;
    }
    
    for(int f = 0 ; f< totalFotogramas;f++){
            cout<<"he entrado "<<f<<endl;
            
        for(int j = 0 ;j<animacion[f];j++){
           sprites[f][j] = new sf::Sprite(*tex);
           sprites[f][j]->setScale(4,4);
           sprites[f][j]->setTextureRect(IntRect(54*j,77*f, 54, 77));
           sprites[f][j]->setPosition(150,50);
           sprites[f][j]->setOrigin(sprites[f][j]->getLocalBounds().width/2,sprites[f][j]->getLocalBounds().height/2);
           sprites[f][j]->setOrigin(15,0);
  
        }       
    }
     if(!sprites){
        cout<<"no se ha podido reservar"<<endl;
    }
    speed = 0.5f;
    
}

int* Animacion::getNumAnimaciones(){
    return animacion;   
}

Sprite Animacion::getSprite(int animacion ,int pos) {
    
    return *sprites[animacion][pos];
}

Sprite Animacion::getSpriteE(){
    
    return ***sprites;
}

void Animacion::orientacion(int orientacion){
    int escala = 0;
    ORIENTACION=orientacion;
    if(orientacion ==0){//miramos a la izq
        escala = -4;
    }
    else{
        escala = 4;
    }
     for(int f = 0 ; f< 8;f++){
                for(int j = 0 ;j<animacion[f];j++){
                    sprites[f][j]->setScale(escala,4);
                    //sprites[f][j]->setPosition(150,50);
                }
            } 
}


void Animacion::movimiento(Vector2f vector){
    
    for(int f = 0 ; f< 8;f++){
                for(int j = 0 ;j<animacion[f];j++){
                    sprites[f][j]->move(vector);  
                }
            } 
}



