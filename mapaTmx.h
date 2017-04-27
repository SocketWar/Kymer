#ifndef MAPATMX_H
#define MAPATMX_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

using namespace std;
using namespace sf;
using namespace tinyxml2;

class mapaTmx {
public:
    mapaTmx();
    void CargaPropiedades();
    void MuestraMapa(RenderWindow &window);
    void Muestrainfo();
    
    int width;
    int height;
    //Vector2i dimension;
    Vector2i tileSheetDim;
    
    int tileSheetWidth;
    int tileSheetHeight;
    
    //int imageSheet
    
    int size;
    int space;
    int numlayers;
    
    Texture *tex;
    XMLDocument *doc;
    XMLElement *map;
    XMLElement *tileset;
    XMLElement *image;
    
    Sprite ****tilemapSprite;
    int ***tilemap;
    
    XMLElement *layer;
    Sprite *sprites;
    
    XMLElement *lay;
    XMLElement *data;
    
    
private:

};

#endif /* MAPATMX_H */

