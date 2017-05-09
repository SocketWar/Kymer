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
    bool load(const string& tileset);
    FloatRect** getColisiones();
    int getnObjetos();
private:
    void CargaPropiedades();
    Vector2i gidToPixel(int gid);
    void Muestrainfo();
    void CargaObjetos();

    Vector2i dimEnTiles;
    Vector2i dimTiles;
    Vector2i dimTileSheet;
    Vector2i nElementos;

    int tileCount;
    int espaciado;
    int nCapas;
    int nObjetos;

    Texture *tex;
    XMLDocument *doc;
    XMLElement *map;
    XMLElement *tileset;
    XMLElement *image;

    int ***tileSheet; //Valor gid de capa tile

    Sprite *sprites;

    XMLElement *layer;
    XMLElement *lay;
    XMLElement *data;
    FloatRect **colisiones; //Array de colisiones
    VertexArray m_vertices; //Lo que se dibuja


    virtual void draw(RenderTarget& target, RenderStates states) const;



};

#endif /* MAPATMX_H */