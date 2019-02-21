#include "mandelbrot.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");
    window.setFramerateLimit(10);

    MandelBrot mandelbrot(window.getSize().x, window.getSize().y);
    mandelbrot.go();

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        window.close();
                    }
                    else if(event.key.code == sf::Keyboard::Z)
                    {
                        mandelbrot.control("zoomIn");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::X)
                    {
                        mandelbrot.control("zoomOut");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::Left
                            || event.key.code == sf::Keyboard::H)
                    {
                        mandelbrot.control("moveLeft");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::Right
                            || event.key.code == sf::Keyboard::L)
                    {
                        mandelbrot.control("moveRight");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::Up
                            || event.key.code == sf::Keyboard::K)
                    {
                        mandelbrot.control("moveUp");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::Down
                            || event.key.code == sf::Keyboard::J)
                    {
                        mandelbrot.control("moveDown");
                        mandelbrot.go();
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        /*sf::Font font;
        font.loadFromFile("IBMPlexMono.ttf");
        sf::Text text("hello", font);
        text.setCharacterSize(10);
        text.setPosition(10, 10);
        text.setFillColor(sf::Color::Black);*/

        window.clear();
        window.draw(mandelbrot.getArray());
        //window.draw(text);
        window.display();
    }

    return 0;
}
