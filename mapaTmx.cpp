#include "mapaTmx.h"

mapaTmx::mapaTmx() {
    cout << "ENTRADO EN CONSTRUCTOR" << endl;

    const string texStr = "res/img/sheet.png";

    cout << "CARGANDO LA TEXTURA...";
    tex = new Texture();
    if (!tex->loadFromFile(texStr)) {
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

    nElementos.x = dimTileSheet.x / (dimTiles.x + espaciado);
    nElementos.y = dimTileSheet.y / (dimTiles.y + espaciado);

    cout << "CREANDO LAS CAPAS...";
    layer = map->FirstChildElement("layer");
    nCapas = 0;
    while (layer) {
        nCapas++;
        layer = layer->NextSiblingElement("layer");
    }
    cout << "OK" << endl;

    cout << "CREANDO LOS SPRITES DE CAPAS...";
    sprites = new Sprite[tileCount];
    for (int c = 0; c < tileCount; c++) {
        sprites[c].setTexture(*tex);
        sprites[c].setTextureRect(IntRect(c * dimTiles.x + espaciado, 0, dimTiles.x, dimTiles.y));
    }
    cout << "OK" << endl;

    cout << "CARGANDO EL TILESHEET...";
    tileSheet = new int**[nCapas];
    for (int i = 0; i < nCapas; i++) {
        tileSheet[i] = new int*[dimEnTiles.y];
        for (int y = 0; y < dimEnTiles.y; y++) {
            tileSheet[i][y] = new int[dimEnTiles.x];
        }
    }
    cout << "OK" << endl;

    cout << "COGIENDO LOS LAYER Y DATA DE TMX...";
    lay = map->FirstChildElement("layer");
    data = lay->FirstChildElement("data")->FirstChildElement("tile");
    for (int l = 0; l < nCapas; l++) {
        for (int y = 0; y < dimEnTiles.y; y++) {
            for (int x = 0; x < dimEnTiles.x; x++) {
                data->QueryIntAttribute("gid", &tileSheet[l][y][x]);
                data = data->NextSiblingElement("tile");
            }
        }
        if (l < nCapas - 1) {
            lay = lay->NextSiblingElement("layer");
            data = lay->FirstChildElement("data")->FirstChildElement("tile");
        }
    }
    cout << "OK" << endl;

    CargaObjetos();
    
    if (load(texStr))
        cout << "LOAD...OK" << endl;

    //Muestrainfo();
}

/*
 * Carga de mapa.
 */
bool mapaTmx::load(const string &tileset) {
    if (!tex->loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(dimEnTiles.x * dimEnTiles.y * 4);

    // 1 Quad por cada elemento del VertexArray
    cout << "INICIALIZANDO LOS TILEMAP...";
    for (int l = 0; l < nCapas; l++) {
        for (unsigned int y = 0; y < dimEnTiles.x; ++y) {
            for (unsigned int x = 0; x < dimEnTiles.y; ++x) {

                int gid = tileSheet[l][x][y];

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

                    quad[0].position = primero;
                    quad[1].position = segundo;
                    quad[2].position = tercero;
                    quad[3].position = cuarto;

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

    cout << "OK" << endl;
    return true;
}

/*
 * Conversor que transforma, a partir de un gid
 *   del tileSheet a una posicion en pixeles de la 
 *   imagen, para su posterior recortado y dibujado.
 */
Vector2i mapaTmx::gidToPixel(int gid) {
    Vector2i res(0.00, 0.00);
    gid = gid - 1;
    res.x = gid % nElementos.x;
    //cout << endl << "SOBRANTE => " << res.x;

    res.x = res.x * dimTiles.x + res.x * espaciado;
    res.y = (gid / nElementos.x);

    //cout << ", " << res.y << endl;

    res.y = res.y * dimTiles.y + res.y * espaciado;

    return res;
}

/*
 * Metodo para depuracion. Muestra infor de variables del mapa.
 */
void mapaTmx::Muestrainfo() {
    cout << "------- DATOS -------" << endl;
    cout << "DIMENSIONES EN TILES: " << dimEnTiles.x << ", " << dimEnTiles.y << endl;
    cout << "DIMENSION DEL TILE: " << dimTiles.x << ", " << dimTiles.y << endl;
    cout << "DIMENSION DEL TILESHEET: " << dimTileSheet.x << ", " << dimTileSheet.y << endl;
    cout << "NUM ELEMENTOS TILESHEET: " << nElementos.x << ", " << nElementos.y << endl;
    cout << "NUM DE TILES: " << tileCount << endl;
    cout << "ESPACIADO: " << espaciado << endl;
    cout << "NUM DE CAPAS: " << nCapas << endl;
    cout << "------- DATOS -------" << endl;
}

/*
 * Metodo que recorre el tmx cargando las variables
 *   principales. Ancho, alto, numero de celdas,
 *   ancho de celdas, alto de celdas, etc
 */
void mapaTmx::CargaPropiedades() {
    cout << "CREANDO LOS XML ELEMENT...";
    XMLError err;
    //-------------------------
    // MAP
    //-------------------------
    err = map->QueryIntAttribute("width", &dimEnTiles.x);
    if (err != 0)
        cout << "ERROR EN WIDTH: " << XMLDocument::ErrorIDToName(err) << endl;

    err = map->QueryIntAttribute("height", &dimEnTiles.y);
    if (err != 0)
        cout << "ERROR EN HEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;

    err = map->QueryIntAttribute("tilewidth", &dimTiles.x);
    if (err != 0)
        cout << "ERROR EN TILEWIDTH: " << XMLDocument::ErrorIDToName(err) << endl;

    err = map->QueryIntAttribute("tileheight", &dimTiles.y);
    if (err != 0)
        cout << "ERROR EN TILEHEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;

    //-------------------------
    // TILESET
    //-------------------------
    tileset = map->FirstChildElement("tileset");
    err = tileset->QueryIntAttribute("tilecount", &tileCount);
    if (err != 0)
        cout << "ERROR EN TILECOUNT: " << XMLDocument::ErrorIDToName(err) << endl;

    //SI HAY ERROR EN EL SPACING SE PONE A 0
    if (tileset->QueryIntAttribute("spacing", &espaciado)) {
        cout << "ERROR EN SPACING: ESTABLECIDO A 0 ....";
        espaciado = 0;
    }

    //-------------------------
    // IMAGE
    //-------------------------
    image = tileset->FirstChildElement("image");
    err = image->QueryIntAttribute("width", &dimTileSheet.x);
    if (err != 0)
        cout << "ERROR EN DIMENSION TILE SHEET WIDTH: " << XMLDocument::ErrorIDToName(err) << endl;

    err = image->QueryIntAttribute("height", &dimTileSheet.y);
    if (err != 0)
        cout << "ERROR EN ERROR EN DIMENSION TILE SHEET HEIGHT: " << XMLDocument::ErrorIDToName(err) << endl;

    if (err == 0)
        cout << "OK" << endl;
}

/*
 * Metodo para la carga de objetos para las colisiones.
 * Carga la primera capa de archivo de .tmx de tipo object
 * TODO: Recorrer todas las capas y diferenciar entre 
 *   colisiones y spawn de enemigos y trofeos
 * 
 */
void mapaTmx::CargaObjetos() {
    cout << "CARGANDO OBJETOS...";
    layer = map->FirstChildElement("objectgroup")->FirstChildElement("object");
    int nObjetos = 0;
    while (layer) {
        nObjetos++;
        layer = layer->NextSiblingElement("object");
    }
    cout << " ENCONTRADOS " << nObjetos << " OBJETOS DE COLISIONES" << endl;
    
    cout << "CREANDO OBJETOS DE COLISIONES...";
    colisiones = new IntRect*[nObjetos];
    layer = map->FirstChildElement("objectgroup")->FirstChildElement("object");
    
    string nombreCapa = map->FirstChildElement("objectgroup")->Attribute("name");
    
    nObjetos = 0;
    float x, y, ancho, alto;
    x = y = ancho = alto = 0;
    while (layer) {
        layer->QueryFloatAttribute("x", &x);
        layer->QueryFloatAttribute("y", &y);
        layer->QueryFloatAttribute("width", &ancho);
        layer->QueryFloatAttribute("height", &alto);
        colisiones[nObjetos] = new IntRect(x, y, ancho, alto);
        nObjetos++;
        layer = layer->NextSiblingElement("object");
    }
    cout << "OK" << endl;
}

IntRect** mapaTmx::getColisiones(){
    return colisiones;
}

void mapaTmx::draw(RenderTarget &target, RenderStates states) const {
    //Aplicamos transformaciones
    states.transform *= getTransform();

    //Se aplica las texturas
    states.texture = tex;

    //Dibujamos el array de vertices (quads)
    target.draw(m_vertices, states);
}