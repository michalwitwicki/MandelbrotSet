#include "mandelbrot.h"

#define X_COORD -0.25
#define Y_COORD 0
#define INIT_OUT_HEIGHT 3
#define MAX_ITER 25

#define ZOOM_JUMP 15 //in percentage

MandelBrot::MandelBrot(int window_width, int window_height)
{
    double init_out_width = double((window_width*INIT_OUT_HEIGHT)/window_height);
    window_size.first = window_width;
    window_size.second = window_height;

    out_ver_range.first = 1.0 * Y_COORD - 1.0 * INIT_OUT_HEIGHT/2;
    out_ver_range.second = 1.0 * Y_COORD + 1.0 * INIT_OUT_HEIGHT/2;
    out_hor_range.first = 1.0 * X_COORD - init_out_width/2;
    out_hor_range.second = 1.0 * X_COORD + init_out_width/2;

    points_arr = sf::VertexArray(sf::Points, window_width*window_height);

    max_iter = MAX_ITER;

    cout<<endl<<out_ver_range.second<<endl;
}

int MandelBrot::mainEquation()
{
    int a = 4;
    //tu beda glowne obliczenia   
    return a;
}

void MandelBrot::go()
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
    double slope_a = (out_hor_range.second-out_hor_range.first) / (window_size.first);
    double slope_b = (out_ver_range.second-out_ver_range.first) / (window_size.second);

    //unsigned int max_iterations = 100;
    unsigned int counter = 0;

    //sf::Color color1 = sf::Color::Black;
    //sf::Color color2 = sf::Color::White;

    for(int i=0; i<window_size.second; ++i)
    {
        for(int j=0; j<window_size.first; ++j)
        {
            //mapping values
            coord_real = slope_a * j + out_hor_range.first;
            coord_imaginary = slope_b * i + out_ver_range.first;

            prev_real = coord_real;
            prev_imaginary = coord_imaginary;

            counter = 0;
            for(counter=0; counter<max_iter; counter++)
            {
                next_real = prev_real*prev_real - prev_imaginary*prev_imaginary; 
                next_imaginary = 2*prev_real*prev_imaginary;

                prev_real = next_real + coord_real;
                prev_imaginary = next_imaginary + coord_imaginary;

                //if((prev_real + prev_imaginary) >= 2)
                if(sqrt(prev_real*prev_real + prev_imaginary*prev_imaginary) >= 2)
                {
                    break;
                }
            }

            points_arr[i*window_size.first + j].position = sf::Vector2f(j, i);
            points_arr[i*window_size.first + j].color = generateColor(counter, prev_real, prev_imaginary);
            /*if(counter == max_iterations)
            {
                points_arr[i*window_size.first + j].color = color1;
            }
            else
            {
                points_arr[i*window_size.first + j].color = color2;
            }*/

        }
    }
}

void MandelBrot::control(string option)
{
    double hor_diff = out_hor_range.second - out_hor_range.first;
    double ver_diff = out_ver_range.second - out_ver_range.first;

    double hor_move = (hor_diff * ZOOM_JUMP) / 200;
    double ver_move = (ver_diff * ZOOM_JUMP) / 200;

    if(option == "zoomIn")
    {
        out_hor_range.first += hor_move;
        out_hor_range.second -= hor_move;

        out_ver_range.first += ver_move;
        out_ver_range.second -= ver_move;
    }
    else if(option == "zoomOut")
    {
        out_hor_range.first -= hor_move;
        out_hor_range.second += hor_move;

        out_ver_range.first -= ver_move;
        out_ver_range.second += ver_move;
    }
    else if(option == "moveLeft")
    {
        out_hor_range.first -= hor_move;
        out_hor_range.second -= hor_move;
    }
    else if(option == "moveRight")
    {
        out_hor_range.first += hor_move;
        out_hor_range.second += hor_move;
    }
    else if(option == "moveUp")
    {
        out_ver_range.first -= hor_move;
        out_ver_range.second -= hor_move;
    }
    else if(option == "moveDown")
    {
        out_ver_range.first += hor_move;
        out_ver_range.second += hor_move;
    }
    else
    {
        cout<<"Error\n";
    }

}

sf::VertexArray MandelBrot::getArray()
{
    return points_arr;
}

sf::Color MandelBrot::generateColor(unsigned int iterations, double prev_real, double prev_imaginary)
{
    sf::Color color;

    if(iterations == max_iter)
    {
        color = sf::Color(40, 40, 40);
    }
    else
    {
        double smooth;
        int coef;
        smooth = iterations + 1;
        smooth -= log(log(sqrt(prev_real*prev_real + prev_imaginary*prev_imaginary))) / log(2);
        smooth *= 1000;
        coef = int(smooth);
        //cout<<smooth<<"|\t";
        color = sf::Color(coef%154, 100, 100);
    }

    return color;
}
