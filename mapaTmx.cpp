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
    sprites = new Sprite[size];
    for (int c = 0; c < size; c++) {
        sprites[c].setTexture(*tex);
        sprites[c].setTextureRect(
            IntRect(c*tileSheetDim.x + space, 0, tileSheetDim.x, tileSheetDim.y));
    }
    cout << "OK" << endl;
    
    cout << "CREANDO LOS SPRITES...";
    tilemap = new int**[numlayers];
    for (int i = 0; i < numlayers; i++) {
        tilemap[i] = new int*[height];
    }
    cout << "OK" << endl;
    
    cout << "CREANDOS LOS TILEMAP 1...";
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < height; y++) {
            tilemap[l][y] = new int[width];
        }
    }
    cout << "OK" << endl;

    cout << "INICIALIZANDO LOS TILEMAP 1...";
    tilemapSprite = new Sprite***[numlayers];

    for (int l = 0; l < numlayers; l++) {
        tilemapSprite[l] = new sf::Sprite**[height];
    }
    cout << "OK" << endl;
    
    cout << "INICIALIZANDOS LOS TILEMAP 2...";
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < height; y++) {
            tilemapSprite[l][y] = new Sprite*[width];
            for (int x = 0; x < width; x++) {
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
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
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
    Muestrainfo();
}

void mapaTmx::CargaPropiedades(){
    cout << "CREANDO LOS XML ELEMENT...";
    XMLError err;
    //-------------------------
    // MAP
    //-------------------------
    err = map->QueryIntAttribute("width", &width);
    if(err != 0)
        cout << "ERROR EN WIDTH: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = map->QueryIntAttribute("height", &height);
    if(err != 0)
        cout << "ERROR EN HEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = map->QueryIntAttribute("tilewidth", &tileSheetDim.x);
    if(err != 0)
        cout << "ERROR EN TILEWIDTH: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = map->QueryIntAttribute("tileheight", &tileSheetDim.y);
    if(err != 0)
        cout << "ERROR EN TILEHEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    //-------------------------
    // TILESET
    //-------------------------
    
    tileset = map->FirstChildElement("tileset");
    err = tileset->QueryIntAttribute("tilecount", &size);
    if(err != 0)
        cout << "ERROR EN TILECOUNT: " << XMLDocument::ErrorIDToName(err) << endl;
    
    err = tileset->QueryIntAttribute("spacing", &space);
    if(err != 0)
        cout << "ERROR EN SPACING: " << XMLDocument::ErrorIDToName(err) << endl;
    
    //-------------------------
    // IMAGE
    //-------------------------
    image = tileset->FirstChildElement("image");
    err = image->QueryIntAttribute("width", &space);
    if(err != 0)
        cout << "ERROR EN SPACING: " << XMLDocument::ErrorIDToName(err) << endl;
    
    if(err == 0)
        cout << "OK" << endl;
    
    
}

void mapaTmx::MuestraMapa(RenderWindow &window) {
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int gid = tilemap[l][y][x] - 1;
                if (gid >= 0) {
                    tilemapSprite[l][y][x]->setTextureRect(sprites[gid].getTextureRect());
                    tilemapSprite[l][y][x]->setPosition(
                        x * tileSheetDim.x, y * tileSheetDim.y);                    
                    window.draw(*tilemapSprite[l][y][x]);
                } else {
                    tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }
}

void mapaTmx::Muestrainfo(){
    cout << "------- DATOS -------" << endl;
    cout << "WIDTH: " << width << endl;
    cout << "HEIGHT: " << height << endl;
    cout << "TILE WIDTH: " << tileSheetDim.x << endl;
    cout << "TILE HEIGHT: " << tileSheetDim.y << endl;
    cout << "SIZE: " << size << endl;
    cout << "SPACE: " << space << endl;
    cout << "N LAYERS: " << numlayers << endl;
    cout << "------- DATOS -------" << endl;
    
    
}