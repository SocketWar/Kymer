
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Animacion.h"

class Enemigo {
public:
    Enemigo();
    Animacion getAnimacion();
    Enemigo(const Enemigo& orig);
    virtual ~Enemigo();
     void Movimiento(Time &tiempo);
      int getActual();
      int getframeActual(Time &tiempo);
      RectangleShape gethitBox();
private:
 int totalSpritesAnimacion;
     int actual;
 float velocidadAnimacion;
    Animacion *animacion;
    float velocidadmovimiento;
    RectangleShape hitBox;
};

#endif /* ENEMIGO_H */