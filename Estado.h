
#include "cabecera.hpp"

class Estado {
public:
    
    Estado(float x,float y);
    void actualizartiempo(float posicionx,float posiciony);
    float getx();
    float gety();
private:

    float posx;
    float posy;
};



