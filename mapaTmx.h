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
    void MuestraMapa(RenderWindow &window);
    
private:
    void CargaPropiedades();
    void CalculaElementos();
    Vector2i gidToPos(int gid);
    void Muestrainfo();

    Vector2i dimEnTiles;
    Vector2i dimTiles;
    Vector2i dimTileSheet;
    Vector2i nElementos;
    
    int tileCount;
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
};

#endif /* MAPATMX_H */

