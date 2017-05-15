
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Animacion.h"
#include "Jugador.h"

class Enemigo {
public:
    Enemigo();
    Animacion getAnimacion();
    Enemigo(const Enemigo& orig);
    virtual ~Enemigo();
     void Movimiento(Time &tiempo, Jugador jugador);
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
    int random;
    bool sorpresa;
    int time1;
    int time_aux;
    sf::Clock *c;
};

#endif /* ENEMIGO_H */