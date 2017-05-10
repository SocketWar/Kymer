

#ifndef SCREEN_1_HPP
#define SCREEN_1_HPP

#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class screen_1 : public cScreen {
private:
    float movement_step;
    float posx;
    float posy;
    sf::RectangleShape Rectangle;
    
public:
    screen_1(void);
    virtual int Run(RenderWindow &App);
    
};

#endif /* SCREEN_1_HPP */

