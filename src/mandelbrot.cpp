#include "mandelbrot.h"
#include "color_conversion.h"
#include "stopwatch.h"

/*#define X_COORD -0.79983
#define Y_COORD -0.17823
#define INIT_OUT_HEIGHT 0.01719
#define MAX_ITER 100*/
#define X_COORD -0.25
#define Y_COORD 0
#define INIT_OUT_HEIGHT 3
#define MAX_ITER 20

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
}

int MandelBrot::mainEquation()
{
    int a = 4;
    //tu beda glowne obliczenia   
    return a;
}

void MandelBrot::go()
{
   //computeMaxIter();
    Stopwatch clock;
    clock.tick();
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

    unsigned int counter = 0;

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
            while(counter < max_iter)
            {
                next_real = prev_real*prev_real - prev_imaginary*prev_imaginary; 
                next_imaginary = 2*prev_real*prev_imaginary;

                prev_real = next_real + coord_real;
                prev_imaginary = next_imaginary + coord_imaginary;

                if(prev_real*prev_real + prev_imaginary*prev_imaginary >= 32) //by definitions it should be 4
                {
                    break;
                }
                counter++;
            }

            points_arr[i*window_size.first + j].position = sf::Vector2f(j, i);
            points_arr[i*window_size.first + j].color = generateColor(counter, prev_real, prev_imaginary);
        }
    }

    cout<<endl;
    //cout<<"vmax = "<<vmax<<endl;
    //cout<<"vmin = "<<vmin<<endl;
    clock.tick();
    cout.precision(40);
    cout<<"time = "<<clock.time()<<endl;
    cout<<"x = "<<fixed<<(out_hor_range.first + out_hor_range.second)/2<<endl;
    cout<<"y = "<<fixed<<(out_ver_range.first + out_ver_range.second)/2<<endl;
    cout<<"ver out = "<<fixed<<out_ver_range.second - out_ver_range.first<<endl; 
    cout<<"max_iter = "<<max_iter<<endl;
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
    else if(option == "maxIterUp")
    {
        maxIterUp();
    }
    else if(option == "maxIterDown")
    {
        maxIterDown();
    }
    else if(option == "reset")
    {
        reset();
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
        //color = HSVtoRGB(200, 0.5, 0.15);
        //sf::Color color1 = sf::Color::Black;
    }
    else
    {
        double s; //smooth coef
        s = iterations + 1.0 - log(log(sqrt(prev_real*prev_real + prev_imaginary*prev_imaginary))) / log(2);
        s /= (max_iter);
        //smooth -= log(log(sqrt(prev_real*prev_real + prev_imaginary*prev_imaginary))) / log(2);
        //s = (cos(s * M_PI + M_PI) + 1) / 2;
        
        color = HSVtoRGB(s*360, 0.8, 0.7);
    }

    return color;
}


void MandelBrot::computeMaxIter() //this must be tuned
{
    //iter_max depends on shorter size of window
    if(window_size.first < window_size.second) 
    {
        max_iter = 1/(out_hor_range.second - out_hor_range.first) + 30;
    }
    else
    {
        max_iter = 1/(out_ver_range.second - out_ver_range.first) + 30;
    }
}


void MandelBrot::maxIterUp()
{
    max_iter += 10;
}

void MandelBrot::maxIterDown()
{
    max_iter -= 10;
}

void MandelBrot::reset()
{
    double init_out_width = double((window_size.first*INIT_OUT_HEIGHT)/window_size.second);
    out_ver_range.first = 1.0 * Y_COORD - 1.0 * INIT_OUT_HEIGHT/2;
    out_ver_range.second = 1.0 * Y_COORD + 1.0 * INIT_OUT_HEIGHT/2;
    out_hor_range.first = 1.0 * X_COORD - init_out_width/2;
    out_hor_range.second = 1.0 * X_COORD + init_out_width/2;

    max_iter = MAX_ITER;
}



void MandelBrot::setCoords(unsigned int x, unsigned int y)
{

}
