#ifndef MAPATMX_H
#define MAPATMX_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

using namespace std;
using namespace sf;
using namespace tinyxml2;

class mapaTmx : public Drawable, public Transformable {
public:
    mapaTmx();
    //void MuestraMapa(RenderWindow &window);
    
     bool load(const std::string& tileset);
    
private:
    void CargaPropiedades();
    Vector2i gidToPixel(int gid);
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
    
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    

};

#endif /* MAPATMX_H */