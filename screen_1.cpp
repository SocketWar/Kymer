/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "screen_1.hpp"

screen_1::screen_1(void) {
    movement_step = 5;
    posx = 320;
    posy = 240;
    //Setting sprite
    Rectangle.setFillColor(sf::Color(255, 255, 255, 150));
    Rectangle.setSize(Vector2f(10.0f, 10.0f));
}

int screen_1::Run(RenderWindow &App) {
    Event Event;
    bool Running = true;

    while (Running) {
        //Verifying events
        while (App.pollEvent(Event)) {
            // Window closed
            if (Event.type == Event::Closed) {
                return (-1);
            }
            //Key pressed
            if (Event.type == Event::KeyPressed) {
                switch (Event.key.code) {
                    case Keyboard::Escape:
                        return (0);
                        break;
                    case Keyboard::Up:
                        posy -= movement_step;
                        break;
                    case Keyboard::Down:
                        posy += movement_step;
                        break;
                    case Keyboard::Left:
                        posx -= movement_step;
                        break;
                    case Keyboard::Right:
                        posx += movement_step;
                        break;
                    default:
                        break;
                }
            }
        }

        //Updating
        if (posx > 630)
            posx = 630;
        if (posx < 0)
            posx = 0;
        if (posy > 470)
            posy = 470;
        if (posy < 0)
            posy = 0;
        Rectangle.setPosition(Vector2f(posx, posy));

        //Clearing screen
        App.clear(Color(0, 0, 0, 0));
        //Drawing
        App.draw(Rectangle);
        App.display();
    }

    //Never reaching this point normally, but just in case, exit the application
    return -1;
}
