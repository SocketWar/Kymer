#include "mapaTmx.h"

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
    }
    cout << "OK" << endl;
    
    cout << "CREANDOS LOS TILEMAP 1...";
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < dimEnTiles.y; y++) {
            tilemap[l][y] = new int[dimEnTiles.x];
        }
    }
    cout << "OK" << endl;

    cout << "INICIALIZANDO LOS TILEMAP 1...";
    tilemapSprite = new Sprite***[numlayers];

    for (int l = 0; l < numlayers; l++) {
        tilemapSprite[l] = new sf::Sprite**[dimEnTiles.y];
    }
    cout << "OK" << endl;
    
    cout << "INICIALIZANDOS LOS TILEMAP 2...";
    for (int l = 0; l < numlayers; l++) {
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
    if(err != 0)
        cout << "ERROR EN SPACING: " << XMLDocument::ErrorIDToName(err) << endl;
    
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
    
    CalculaElementos();
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

void mapaTmx::CalculaElementos(){
    cout << "------- CALCULOS -------" << endl;
    
    nElementos.x = dimTileSheet.x / (dimTiles.x + space);
    nElementos.y = dimTileSheet.y / (dimTiles.y + space);
    
    cout << "nElementos: " << nElementos.x << ", " << nElementos.y << endl;
    
    Vector2i aux;
    aux = gidToPos(150);
    cout << "AUX(150): " << aux.x << ", " << aux.y << endl;
    aux = gidToPos(145);
    cout << "AUX(145): " << aux.x << ", " << aux.y << endl;
    aux = gidToPos(6);
    cout << "AUX(6): " << aux.x << ", " << aux.y << endl;
    
    cout << "------- CALCULOS -------" << endl;
}

Vector2i mapaTmx::gidToPos(int gid) {
    // IDENTIFICADOR / NUM ELEMENTOS EN ANCHO PARA LA Y
    // (IDENTIFICADOR % NUM ELEMENTOS EN ANCHO ) * NUM ELEMENTOS EN ANCHO PARA X
    Vector2i res(0.00, 0.00);

    res.x = gid % nElementos.x;
    res.x = res.x * dimTiles.x;
    res.y = (gid / nElementos.x) + 1;
    res.y = res.y * dimTiles.y;

    return res;
}

void mapaTmx::Muestrainfo(){
    cout << "------- DATOS -------" << endl;
    cout << "WIDTH: " << dimEnTiles.x << endl;
    cout << "HEIGHT: " << dimEnTiles.y << endl;
    cout << "TILE WIDTH: " << dimTiles.x << endl;
    cout << "TILE HEIGHT: " << dimTiles.y << endl;
    cout << "DIM TILESHEET: " << dimTileSheet.x << ", " << dimTileSheet.y << endl;
    cout << "NUM ELEMENTOS: " << nElementos.x << ", " << nElementos.y << endl;
    cout << "SIZE: " << tileCount << endl;
    cout << "SPACE: " << space << endl;
    cout << "N LAYERS: " << numlayers << endl;
    cout << "------- DATOS -------" << endl;
}