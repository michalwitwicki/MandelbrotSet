#include "ui.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 750

static sf::RenderWindow window;

void start_ui()
{
    window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");

    window.setFramerateLimit(10);
}

void main_loop()
{

}
