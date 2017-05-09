#include "mapaTmx.h"

mapaTmx::mapaTmx(){
    cout << "ENTRADO EN CONSTRUCTOR" << endl;

    cout << "CARGANDO LA TEXTURA...";
    tex = new Texture();
    if (!tex->loadFromFile("res/img/tiles_2.png")) {
        cerr << "Error cargando la textura";
        exit(0);
    }
    cout << "OK" << endl;

    cout << "CARGANDO EL MAPA...";
    doc = new XMLDocument();
    doc->LoadFile("res/tmx/s2.tmx");
    cout << "OK" << endl;
    
    cout << "CREANDO EL XML DOCUMENT.....";
    map = doc->FirstChildElement("map");
    cout << "OK" << endl;
    
    CargaPropiedades();
    
    nElementos.x = dimTileSheet.x / (dimTiles.x + space);
    nElementos.y = dimTileSheet.y / (dimTiles.y + space);
    
    cout << "CREANDO LAS CAPAS...";
    layer = map->FirstChildElement("layer");
    numlayers = 0;
    while (layer) {
        numlayers++;
        layer = layer->NextSiblingElement("layer");
    }
    cout << "OK" << endl;
    
    cout << "CREANDO LOS SPRITES DE CAPAS...";
    sprites = new Sprite[tileCount];
    for (int c = 0; c < tileCount; c++) {
        sprites[c].setTexture(*tex);
        sprites[c].setTextureRect(IntRect(c*dimTiles.x + space, 0, dimTiles.x, dimTiles.y));
    }
    cout << "OK" << endl;
    
    cout << "CREANDO LOS SPRITES...";
    tilemap = new int**[numlayers];
    for (int i = 0; i < numlayers; i++) {
        tilemap[i] = new int*[dimEnTiles.y];
        for (int y = 0; y < dimEnTiles.y; y++) {
            tilemap[i][y] = new int[dimEnTiles.x];
        }
    }
    cout << "OK" << endl;
    
    cout << "INICIALIZANDO LOS TILEMAP 1...";
    tilemapSprite = new Sprite***[numlayers];

    for (int l = 0; l < numlayers; l++) {
        tilemapSprite[l] = new Sprite**[dimEnTiles.y];
        for (int y = 0; y < dimEnTiles.y; y++) {
            tilemapSprite[l][y] = new Sprite*[dimEnTiles.x];
            for (int x = 0; x < dimEnTiles.x; x++) {
                tilemapSprite[l][y][x] = new Sprite(*tex);
            }
        }
    }
    cout << "OK" << endl;
    
    cout << "CREANDO LOS TILEMAP 2...";
    lay = map->FirstChildElement("layer");
    data = lay->FirstChildElement("data")->FirstChildElement("tile");
    cout << "OK" << endl;
    
    cout << "COGIENDO LOS LAYER Y DATA DE TMX...";
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < dimEnTiles.y; y++) {
            for (int x = 0; x < dimEnTiles.x; x++) {
                data->QueryIntAttribute("gid", &tilemap[l][y][x]);
                data = data->NextSiblingElement("tile");
            }
        }
        if (l < numlayers - 1) {
            lay = lay->NextSiblingElement("layer");
            data = lay->FirstChildElement("data")->FirstChildElement("tile");
        }
    }
    cout << "OK" << endl;
    
    if(load("res/img/tiles_2.png"))
        cout<< "LOAD...OK" << endl;
    
    //Muestrainfo();
}

bool mapaTmx::load(const string &tileset) {
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(dimEnTiles.x * dimEnTiles.y * 4);

    // 1 Quad por cada elemento del VertexArray
    for (int l = 0; l < numlayers; l++) {
        for (unsigned int y = 0; y < dimEnTiles.x; ++y) {
            for (unsigned int x = 0; x < dimEnTiles.y; ++x) {
                
                int gid = tilemap[l][x][y];
                
                if (gid > 0) {
                    // get a pointer to the current tile's quad
                    Vertex *quad = &m_vertices[(y + x * dimEnTiles.x) * 4];

                    // Posicion del cuadrado
                    Vector2f primero(y * dimTiles.x, x * dimTiles.y);
                    Vector2f segundo((y + 1) * dimTiles.x, x * dimTiles.y);
                    Vector2f tercero((y + 1) * dimTiles.x, (x + 1) * dimTiles.y);
                    Vector2f cuarto(y * dimTiles.x, (x + 1) * dimTiles.y);
                    
                    /*
                    cout << endl << "GID: " << gid-1 << endl;
                    cout << "POSICION => [" << primero.x << ", " << primero.y << "] ";
                    cout << "[" << segundo.x << ", " << segundo.y << "] ";
                    cout << "[" << tercero.x << ", " << tercero.y << "] ";
                    cout << "[" << cuarto.x << ", " << cuarto.y << "] " << endl;
                     */
                    
                    quad[0].position = primero;//fondo
                    quad[1].position = segundo;//suelo
                    quad[2].position = tercero;//objetos
                    quad[3].position = cuarto;//enemigos

                    // Textura para la pieza
                    Vector2i pxCords = gidToPixel(gid);
                    
                    Vector2f recorte1(pxCords.x, pxCords.y);
                    Vector2f recorte2(pxCords.x + dimTiles.x, pxCords.y);
                    Vector2f recorte3(pxCords.x + dimTiles.x, pxCords.y + dimTiles.y);
                    Vector2f recorte4(pxCords.x, pxCords.y + dimTiles.y);
                    
                    /*
                    cout << "RECORTE => [" << recorte1.x << ", " << recorte1.y << "] ";
                    cout << "[" << recorte2.x << ", " << recorte2.y << "] ";
                    cout << "[" << recorte3.x << ", " << recorte3.y << "] ";
                    cout << "[" << recorte4.x << ", " << recorte4.y << "] " << endl;
                    */
                    
                    quad[0].texCoords = recorte1;
                    quad[1].texCoords = recorte2;
                    quad[2].texCoords = recorte3;
                    quad[3].texCoords = recorte4;
                }
            }
        }
    }

    return true;
}

Vector2i mapaTmx::gidToPixel(int gid) {
    Vector2i res(0.00, 0.00);
    gid = gid - 1;
    res.x = gid % nElementos.x;
    //cout << endl << "SOBRANTE => " << res.x;
    
    res.x = res.x * dimTiles.x + res.x * space;
    res.y = (gid / nElementos.x);
    
    //cout << ", " << res.y << endl;
    
    res.y = res.y * dimTiles.y  + res.y * space;

    return res;
}

void mapaTmx::Muestrainfo(){
    cout << "------- DATOS -------" << endl;
    cout << "DIMENSIONES EN TILES: " << dimEnTiles.x << ", "<< dimEnTiles.y << endl;
    cout << "DIMENSION DEL TILE: " << dimTiles.x << ", "<< dimTiles.y << endl;
    cout << "DIMENSION DEL TILESHEET: " << dimTileSheet.x << ", " << dimTileSheet.y << endl;
    cout << "NUM ELEMENTOS TILESHEET: " << nElementos.x << ", " << nElementos.y << endl;
    cout << "NUM DE TILES: " << tileCount << endl;
    cout << "ESPACIADO: " << space << endl;
    cout << "NUM DE CAPAS: " << numlayers << endl;
    cout << "------- DATOS -------" << endl;
}



void mapaTmx::CargaPropiedades(){
    cout << "CREANDO LOS XML ELEMENT...";
    XMLError err;
    //-------------------------
    // MAP
    //-------------------------
    err = map->QueryIntAttribute("width", &dimEnTiles.x);
    if(err != 0)
        cout << "ERROR EN WIDTH: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = map->QueryIntAttribute("height", &dimEnTiles.y);
    if(err != 0)
        cout << "ERROR EN HEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = map->QueryIntAttribute("tilewidth", &dimTiles.x);
    if(err != 0)
        cout << "ERROR EN TILEWIDTH: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = map->QueryIntAttribute("tileheight", &dimTiles.y);
    if(err != 0)
        cout << "ERROR EN TILEHEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    //-------------------------
    // TILESET
    //-------------------------
    
    tileset = map->FirstChildElement("tileset");
    err = tileset->QueryIntAttribute("tilecount", &tileCount);
    if(err != 0)
        cout << "ERROR EN TILECOUNT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = tileset->QueryIntAttribute("spacing", &space);
    if(err != 0){
        cout << "ERROR EN SPACING: " << XMLDocument::ErrorIDToName(err) << endl;
        space= 0;
    }
    //-------------------------
    // IMAGE
    //-------------------------
    image = tileset->FirstChildElement("image");
    err = image->QueryIntAttribute("width", &dimTileSheet.x);
    if(err != 0)
        cout << "ERROR EN DIMENSION TILE SHEET WIDTH: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = image->QueryIntAttribute("height", &dimTileSheet.y);
    if(err != 0)
        cout << "ERROR EN ERROR EN DIMENSION TILE SHEET HEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    if(err == 0)
        cout << "OK" << endl;
}

/*
mapaTmx::mapaTmx() {
    cout << "ENTRADO EN CONSTRUCTOR" << endl;

    cout << "CARGANDO LA TEXTURA...";
    tex = new Texture();
    if (!tex->loadFromFile("res/img/sheet.png")) {
        cerr << "Error cargando la textura";
        exit(0);
    }
    cout << "OK" << endl;

    cout << "CARGANDO EL MAPA...";
    doc = new XMLDocument();
    doc->LoadFile("res/tmx/gitaner.tmx");
    cout << "OK" << endl;
    
    cout << "CREANDO EL XML DOCUMENT.....";
    map = doc->FirstChildElement("map");
    cout << "OK" << endl;
    
    CargaPropiedades();
    
    nElementos.x = dimTileSheet.x / (dimTiles.x + space);
    nElementos.y = dimTileSheet.y / (dimTiles.y + space);
    
    cout << "CREANDO LAS CAPAS...";
    layer = map->FirstChildElement("layer");
    numlayers = 0;
    while (layer) {
        numlayers++;
        layer = layer->NextSiblingElement("layer");
    }
    cout << "OK" << endl;

    cout << "CREANDO LOS SPRITES DE CAPAS...";
    sprites = new Sprite[tileCount];
    for (int c = 0; c < tileCount; c++) {
        sprites[c].setTexture(*tex);
        sprites[c].setTextureRect(
            IntRect(c*dimTiles.x + space, 0, dimTiles.x, dimTiles.y));
    }
    cout << "OK" << endl;
    
    cout << "CREANDO LOS SPRITES...";
    tilemap = new int**[numlayers];
    for (int i = 0; i < numlayers; i++) {
        tilemap[i] = new int*[dimEnTiles.y];
        for (int y = 0; y < dimEnTiles.y; y++) {
            tilemap[l][y] = new int[dimEnTiles.x];
        }
    }
    cout << "OK" << endl;
    
    cout << "INICIALIZANDO LOS TILEMAP 1...";
    tilemapSprite = new Sprite***[numlayers];

    for (int l = 0; l < numlayers; l++) {
        tilemapSprite[l] = new Sprite**[dimEnTiles.y];
        for (int y = 0; y < dimEnTiles.y; y++) {
            tilemapSprite[l][y] = new Sprite*[dimEnTiles.x];
            for (int x = 0; x < dimEnTiles.x; x++) {
                tilemapSprite[l][y][x] = new Sprite(*tex);
            }
        }
    }
    cout << "OK" << endl;
    
    cout << "CREANDO LOS TILEMAP 2...";
    lay = map->FirstChildElement("layer");
    data = lay->FirstChildElement("data")->FirstChildElement("tile");
    cout << "OK" << endl;
    
    cout << "COGIENDO LOS LAYER Y DATA DE TMX...";
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < dimEnTiles.y; y++) {
            for (int x = 0; x < dimEnTiles.x; x++) {
                data->QueryIntAttribute("gid", &tilemap[l][y][x]);
                data = data->NextSiblingElement("tile");
            }
        }
        if (l < numlayers - 1) {
            lay = lay->NextSiblingElement("layer");
            data = lay->FirstChildElement("data")->FirstChildElement("tile");
        }
    }
    cout << "OK" << endl;
    //Muestrainfo();
} 

void mapaTmx::MuestraMapa(RenderWindow &window) {
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < dimEnTiles.y; y++) {
            for (int x = 0; x < dimEnTiles.x; x++) {
                int gid = tilemap[l][y][x] - 1;
                if (gid >= 0) {
                    tilemapSprite[l][y][x]->setTextureRect(sprites[gid].getTextureRect());
                    tilemapSprite[l][y][x]->setPosition(
                    x * dimTiles.x, y * dimTiles.y);                    
                    window.draw(*tilemapSprite[l][y][x]);
                } else {
                    tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }
}
 */