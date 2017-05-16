
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Animacion.h"
#include "Jugador.h"
#include "Motor2D.h"
class Enemigo {
public:
    Enemigo(int tipoE);
    Animacion getAnimacion();
    Enemigo(const Enemigo& orig);
    virtual ~Enemigo();
    void Movimiento(Time &tiempo, Jugador jugador);
    void UpdateGranada();
    void RenderGranada(RenderWindow &window);
    int getActual();
    int getframeActual(Time &tiempo);
    RectangleShape gethitBox();
    void update(Time &tiempo, Jugador jugador);
    void render(float interpolacion,Time &tiempo);
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
    Clock RelojGranada;
    Clock RelojBala;
    vector<Granada*> CARGADORGRANADA;
    vector<Bala*> CARGADOR;
    sf::Clock *c;
    Estado *viejo;
    Estado *nuevo;
    int tipo;
};

#endif /* ENEMIGO_H */