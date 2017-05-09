

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Animacion.h"

class Enemigo {
public:
    Enemigo();
    Animacion getAnimacion();
    Enemigo(const Enemigo& orig);
    virtual ~Enemigo();
private:

    Animacion *animacion;
};

#endif /* ENEMIGO_H */