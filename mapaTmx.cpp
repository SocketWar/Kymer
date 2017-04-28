#include "mapaTmx.h"

mapaTmx::mapaTmx(){
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
    
    
    
    // define the level with an array of tile indices
    int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 
        0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 
        0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 
        0, 0, 0, 0, 1, 1, 1, 1,
    };
    
    //if (!load("res/img/sheet.png", dimTiles, level, 16, 8))
    if (!load("res/img/sheet.png", dimTiles, tilemap[0][0], Vector2i(16, 8)))
        cout<< "PUTA MIERDA" << endl;
    
    Muestrainfo();
}

bool mapaTmx::load(const string &tileset, Vector2i tileSize, int *tiles, Vector2i dimensiones) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(dimensiones.x * dimensiones.y * 4);

    
    //for (int l = 0; l < numlayers; l++) {
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < dimensiones.x; ++i) {
        for (unsigned int j = 0; j < dimensiones.y; ++j) {
            // get the current tile number
            int tileNumber = tiles[i + j * dimensiones.x];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * dimensiones.x) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}

Vector2i mapaTmx::gidToPixel(int gid) {
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