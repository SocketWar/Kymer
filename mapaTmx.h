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
    void muestraMapa(RenderWindow &window);
    
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    
    Texture *tex;
    XMLDocument *doc;
    XMLElement *map;
    
    Sprite ****tilemapSprite;
    int ***tilemap;
    
    XMLElement *layer;
    int numlayers;
    Sprite *sprites;
    
    XMLElement *lay;
    XMLElement *data;
    
    
private:

};

#endif /* MAPATMX_H */

