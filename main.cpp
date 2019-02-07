#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

void Mandelbrot(sf::VertexArray& points_arr)
{
    //recursive formula for mandelbrot set, c belongs to Imaginary set
    //Z0 = 0
    //Zn+1 = (Zn)^2 + c
    //c = a + bi
    //sqrt(-1) = i
    
    double coord_real; //real component coordinate
    double coord_imaginary; //imaginary component coordinate

    double prev_real;
    double prev_imaginary;

    double next_real;
    double next_imaginary;

    //slopes for later values mapping
    double slope_a = 1.0 * (2-(-2)) / (WINDOW_HEIGHT-0);
    double slope_b = 1.0 * (2-(-2)) / (WINDOW_WIDTH-0);

    unsigned int max_iterations = 100;
    unsigned int counter = 0;

    sf::Color color1 = sf::Color::Black;
    sf::Color color2 = sf::Color::White;

    for(int i=0; i<WINDOW_HEIGHT; ++i)
    {
        for(int j=0; j<WINDOW_WIDTH; ++j)
        {
            //mapping values
            coord_real = slope_a * j + (-2);
            coord_imaginary = slope_b * i + (-2);

            prev_real = coord_real;
            prev_imaginary = coord_imaginary;

            for(counter = 0; counter<max_iterations; ++counter)
            {
                next_real = prev_real*prev_real - prev_imaginary*prev_imaginary; 
                next_imaginary = 2*prev_real*prev_imaginary;

                prev_real = next_real + coord_real;
                prev_imaginary = next_imaginary + coord_imaginary;

                if((prev_real + prev_imaginary) >= 2)
                {
                    break;
                }
            }

            points_arr[i*WINDOW_WIDTH + j].position = sf::Vector2f(j, i);
            if(counter == max_iterations)
            {
                points_arr[i*WINDOW_WIDTH + j].color = color1;
            }
            else
            {
                points_arr[i*WINDOW_WIDTH + j].color = color2;
            }

        }
    }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");
    window.setFramerateLimit(10);

    sf::VertexArray points_arr(sf::Points, WINDOW_WIDTH * WINDOW_HEIGHT);

    Mandelbrot(points_arr);

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
                    window.close();
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        window.clear();
        window.draw(points_arr);
        window.display();
    }

    return 0;
}

