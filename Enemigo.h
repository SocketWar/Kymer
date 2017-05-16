
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
    void Saltar();
    void UpdateGranada();
    void RenderGranada(RenderWindow &window);
    Vector2f getPos();
    int getActual();
    int getframeActual(Time &tiempo);
    void actualizarHitbox();
    void calcularColision(FloatRect** arrayColisiones,int nobjetos);
    RectangleShape gethitBox();
    void update(Time &tiempo, Jugador jugador);
    void render(float interpolacion,Time &tiempo);
private:
    
    Vector2f velocidad; //velocidad en las dos posiciones
    float gravedad;
    int distanciasuelo;
    float velocidadsalto;
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
    //colisiones
    bool suelo;
    bool colision;
    bool estadocolision;
    bool muro;
};

#endif /* ENEMIGO_H */