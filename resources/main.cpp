#include <iostream>
#include <SFML/Graphics.hpp>

#define kVel 5
#define posX_i 0
#define posY_i 0

using namespace std;
using namespace sf;
int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
     window.setFramerateLimit(60);
 
    //Creo mis variables que controlaran los tiempos
    sf::Time tiempoTranscurrido;
    sf::Clock reloj;
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/Walter2.png"))
    {
        std::cerr << "Error cargando la imagen walter.png";
        exit(0);
    }
    tex.setSmooth(false);
    
    // INICIO sprite para el cuerpo 
            sf::Sprite spriteBody(tex);
            sf::Vector2i tamSpriteBody(30, 36); 
            spriteBody.setOrigin(75/2,75/2);
            spriteBody.setTextureRect(sf::IntRect(0, 0, tamSpriteBody.x, tamSpriteBody.y));
            spriteBody.setOrigin(75/2,75/2);//Le pongo el centroide donde corresponde
            spriteBody.setPosition(320, 240);// Lo dispongo en el centro de la pantalla
            spriteBody.setScale(4,4);
    // FIN    sprite para el cuerpo
//    // INICIO sprite para las piernas
//            sf::Sprite spriteLegs(tex);
//            sf::Vector2i tamSpriteLeg(30, 30); 
//            spriteLegs.setOrigin(75/2,75/2);
//            spriteLegs.setTextureRect(sf::IntRect(0, 0, tamSpriteLeg.x, tamSpriteLeg.y));
//            spriteLegs.setOrigin(75/2,75/2);//Le pongo el centroide donde corresponde
//            spriteLegs.setPosition(320, 240);// Lo dispongo en el centro de la pantalla
//            spriteLegs.setScale(4,4);
//    // FIN    sprite para las piernas
    // guardado de animaciones INICIO
            int posParado = 1;
            std::vector<sf::IntRect> parado;
            parado.push_back(sf::IntRect(0,0,tamSpriteBody.x,tamSpriteBody.y));
            parado.push_back(sf::IntRect(tamSpriteBody.x,0,tamSpriteBody.x,tamSpriteBody.y));
            parado.push_back(sf::IntRect(tamSpriteBody.x*2,0,tamSpriteBody.x,tamSpriteBody.y));
    // guardado de animaciones FIN 
    
    float duracionAnimacion = 0.75;
    bool noKeyPressed = true;
    
    int frameActual = 0 ;


    
 
    
    
    //Bucle del juego
    while (window.isOpen())
    {
        //Regresa el tiempo transcurrido y reinicia el reloj
        sf::Time deltaTime = reloj.restart();
 
        //Acumula el tiempo con cada frame que pasa
        tiempoTranscurrido += deltaTime;
         float tiempoEnSegundos = tiempoTranscurrido.asSeconds();
 
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            std::cout<<"posParado"<< posParado<<endl;
                            std::cout<<"parado"<<parado.size()<<endl;
                            spriteBody.setTextureRect(parado[posParado]);
                            //Escala por defecto
                                 
                            if ( posParado == parado.size()){
                                posParado = 0;
                            }else posParado++;
                            
                            //spriteBody.move(kVel,0);
                        break;

                        case sf::Keyboard::Left:
                            spriteBody.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
                            //Reflejo vertical
                           // sprite.setScale(-1,1);
                            spriteBody.move(-kVel,0); 
                        break;
                        
                        case sf::Keyboard::Up:
                            spriteBody.setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
                            spriteBody.move(0,-kVel); 
                        break;
                        
                        case sf::Keyboard::Down:
                            spriteBody.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
                            spriteBody.move(0,kVel); 
                        break;
                        
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }
           
            }
                    if(noKeyPressed){
//                        std::cout<<"tiempoActual : "<<tiempoEnSegundos<<endl;
                        
                        //obtiene el frame de la animacion actual
                          frameActual = static_cast<int>((tiempoEnSegundos / duracionAnimacion) * parado.size()) % parado.size();//a int 
                          spriteBody.setTextureRect(parado[frameActual]);
//                        std::cout<<"frame actual  : "<< frameActual<<endl;
                    }
            
        }

        window.clear(sf::Color::Red);
        window.draw(spriteBody);
        window.display();
    }

    return 0;
}