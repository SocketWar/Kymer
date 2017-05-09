
#ifndef ESTADO_H
#define ESTADO_H

#include "cabecera.hpp"

class Estado {
public:
    
    Estado();
    void actualizartiempo(float posicionx,float posiciony);
    float getx();
    float gety();
    Vector2f getInterpolacion(Estado* viejo,Estado* nuevo, float interpolacion);
private:

    float posx;
    float posy;
};

#endif /* ESTADO_H */

