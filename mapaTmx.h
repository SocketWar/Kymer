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
    mapaTmx(string mapa, string tileSheet);
    bool load(const string& tileset);
    FloatRect** getColisiones();
    Vector2f** getSpawn();
    Vector2f** getPuntuaciones();
    int getnColisiones();
    int getnSpawn();
    int getnPuntos();

    ~mapaTmx();
private:
    void CargaPropiedades();
    Vector2i gidToPixel(int gid);
    void Muestrainfo();
    void CargaObjetos();
    virtual void draw(RenderTarget& target, RenderStates states) const;

    Vector2i dimEnTiles;
    Vector2i dimTiles;
    Vector2i dimTileSheet;
    Vector2i nElementos;

    int tileCount;
    int espaciado;
    int nCapas;
    int nObjetos;
    int nSpawn;
    int nPuntos;
    int ***tileSheet; //Valor gid de capa tile

    Texture *tex;
    Sprite *sprites;
    
    XMLDocument *doc;
    XMLElement *map;
    XMLElement *tileset;
    XMLElement *image;
    XMLElement *layer;
    XMLElement *lay;
    XMLElement *data;

    FloatRect **colisiones; //Array de colisiones
    Vector2f **spawn;       //Puntos de spawn de enemigos
    Vector2f **puntos;      //Puntos de puntuacion
    
    VertexArray m_vertices; //Lo que se dibuja
};

#endif /* MAPATMX_H */