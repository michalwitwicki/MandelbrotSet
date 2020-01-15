#include "mandelbrot.h"
#include "ui.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 750

int main()
{

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
                case sf::Event::MouseButtonPressed:
                {
                    //cout<<event.mouseButton.x<<endl;
                    mandelbrot.setCoords(event.mouseButton.x, event.mouseButton.y);
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
                    else if(event.key.code == sf::Keyboard::U)
                    {
                        mandelbrot.control("maxIterUp");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::P)
                    {
                        mandelbrot.control("maxIterDown");
                        mandelbrot.go();
                    }
                    else if(event.key.code == sf::Keyboard::R)
                    {
                        mandelbrot.control("reset");
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


/* TO DO:
    - podzielic jakos madrze wszystkie rzeczy zwiazane z user inputem
    - successive dwell limit
    - podzielic metode go() na mniejsze czesci
*/
