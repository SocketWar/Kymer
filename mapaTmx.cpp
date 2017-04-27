#include "mapaTmx.h"

mapaTmx::mapaTmx() {
    cout << "ENTRADO EN CONSTRUCTOR" << endl;

    tex = new Texture();
    if (!tex->loadFromFile("res/img/map.png")) {
        cerr << "Error cargando la imagen map.png";
        exit(0);
    }

    cout << "CARGADO EL MAPA" << endl;

    doc = new XMLDocument();
    doc->LoadFile("res/tmx/pru.tmx");
    cout << "CREADO EL XML DOCUMENT" << endl;

    map = doc->FirstChildElement("map");

    cout << "CREADO EL XML ELEMENT" << endl;

    map->QueryIntAttribute("width", &width);
    map->QueryIntAttribute("height", &height);
    map->QueryIntAttribute("tilewidth", &tileWidth);
    map->QueryIntAttribute("tileheight", &tileHeight);

    layer = map->FirstChildElement("layer");
    numlayers = 0;
    while (layer) {
        numlayers++;
        layer = layer->NextSiblingElement("layer");
    }

    cout << "CREADO LAS CAPAS" << endl;

    int size = 5;

    sprites = new Sprite[size];

    for (int c = 0; c < size; c++) {
        sprites[c].setTexture(*tex);
        sprites[c].setTextureRect(IntRect(c*tileWidth, 0, tileWidth, tileHeight));
    }

    cout << "CREADOS LOS SPRITES" << endl;

    tilemap = new int**[numlayers];
    for (int i = 0; i < numlayers; i++) {
        tilemap[i] = new int*[height];
    }

    cout << "CREADOS LOS TILEMAP 1" << endl;

    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < height; y++) {
            tilemap[l][y] = new int[width];
        }
    }

    cout << "INICIALIZADOS LOS TILEMAP 1" << endl;
    
    tilemapSprite = new Sprite***[numlayers];

    for (int l = 0; l < numlayers; l++) {
        tilemapSprite[l] = new sf::Sprite**[height];
    }

    cout << "INICIALIZADOS LOS TILEMAP 2" << endl;
    
    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < height; y++) {
            tilemapSprite[l][y] = new Sprite*[width];
            for (int x = 0; x < width; x++) {
                tilemapSprite[l][y][x] = new Sprite(*tex);
            }
        }
    }


    cout << "CREADOS LOS TILEMAP 2" << endl;

    lay = map->FirstChildElement("layer");
    data = lay->FirstChildElement("data")->FirstChildElement("tile");

    cout << "COGIDOS LOS LAYER Y DATA DE TMX" << endl;

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

    cout << "CREADAS LAS CELDAS" << endl;
}

void mapaTmx::muestraMapa(RenderWindow &window) {
    cout << "INCIO MUESTRA MAPA" << endl;

    for (int l = 0; l < numlayers; l++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int gid = tilemap[l][y][x] - 1;
                cout << "GID: " << gid << endl;

                cout << " X: " << x << " Y: " << y << " L: " << l << endl;
                if (gid >= 0) {
                    tilemapSprite[l][y][x]->setTextureRect(sprites[gid].getTextureRect());
                    tilemapSprite[l][y][x]->setPosition(x*tileWidth, y * tileHeight);
                    window.draw(*tilemapSprite[l][y][x]);
                } else {
                    tilemapSprite[l][y][x] = NULL;
                }
            }
        }
    }
}