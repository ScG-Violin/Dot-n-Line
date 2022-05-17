
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <iostream>
#include "figure.h"
#define Y 1
#define X 0

using namespace sf;

int main()
{
    sf::Font font;
    const std::string fontName("arial.ttf");
    font.loadFromFile(fontName);
    sf::Text text;
    text.setFillColor(sf::Color::Yellow);
    text.setFont(font);
    text.setString("Wake the fuck up, SAMURAI. We have a city to burn!");
    text.setCharacterSize(20);
    text.setPosition(800, 900);

    bool left, right, up, down, switc, stop, res;
    float c_rad = 15.0f, l_line = 100.0f;
    unsigned int win_h = 720, win_w = 1280;
    ContextSettings settings;
    settings.antialiasingLevel = 4;
    MyWin window(win_w, win_h, settings);
    window.setFramerateLimit(60);
    Dot dt(win_w / 2 - c_rad, win_h / 2 - c_rad, c_rad);
    Line ln(win_w / 2 - c_rad, win_h / 2 - c_rad, l_line);
    SimpFigure* circ = &dt;
    dt.setFillColor(Color(250, 0, 0));
    ln.setFillColor(Color(0, 0, 250));
    
    circ->Respawn();

    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            stop = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            res = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
            switc = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            if (left)
                circ->Rotate(-1.0f);

            if (right)
                circ->Rotate(1.0f);

            if (up)
                circ->Acceleration(1.0f);

            if (down)
                circ->Acceleration(-1.0f);

            if (stop)
                circ->Stop();

            if (res) 
                circ->Respawn();

            if (switc) {
                switc = false;
                if (circ == &dt) {
                    circ = &ln;
                }
                else { circ = &dt; }
                std::cout << circ << std::endl;
                circ->Respawn();
                goto exit;
            }

        }
        exit:
        circ->Slow();
        circ->MoveShape();
        window.clear(sf::Color(204,204,204));
        if (circ == &dt)
            window.drawD(dt);
        else window.drawL(ln);
        window.draw(text);
        window.display();
    }

    return 0;
}