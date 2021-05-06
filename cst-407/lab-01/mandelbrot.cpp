//*****************************************************
// Compute mandelbrot set images
//
// Author: Rowan Parker
//*****************************************************

#include <complex>
#include <cstdio>
#include <utility>
#include <vector>

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>      // BMP output uses C IO not C++
#include <time.h>
#include <unistd.h>     // for getopt

#include "bmp.h"        // class for creating BMP files

using std::complex;
using std::vector;
using std::pair;

// mode for which algorithm to use
enum algorithm
{
    SIMPLE = 0,
    THREADED = 1,
    BALANCED = 2
};

// Passed to threads as a parameter
typedef struct
{
    pthread_t id;                               // thread
    int num;                                    // thread number (0-n)
    vector<pair<long double, long double>> c;   // used in ComputeMandelbrot
    vector<pair<int,int>> pixel;                // value location (row, col)
    int max_iters;                              // maximum iterations
    Bmp_c *image;                               // reference to image
    float duration;                             // thread duration
} thread_arg_t;

// function prototypes
void FastThreadedApproach(int rows, int cols, long double start_x, long double end_x, long double start_y, long double end_y, int max_iters, int num_threads, Bmp_c *image);
void FasterThreadedApproach(int rows, int cols, long double start_x, long double end_x, long double start_y, long double end_y, int max_iters, int num_threads, Bmp_c *image);
void SimpleApproach(int rows, int cols, long double start_x, long double end_x, long double start_y, long double end_y, int max_iters, Bmp_c *image);
void *ThreadedComputeMandelbrot(void *a);
int ComputeMandelbrot(long double x, long double y, int max_iters);
int ColorizeMono(int value, int max_value);
int ColorizeScaled(int value, int max_value);

// ******************************************************
// Generates the Mandelbrot set using threaded computation
// Params:
//    Default values for command line args and a reference
//    to the image object
// Return:
//    none
void FastThreadedApproach(int rows, int cols, long double start_x, long double end_x, long double start_y, 
                      long double end_y, int max_iters, int num_threads, Bmp_c *image)
{
    // create thread arg array
    thread_arg_t *args = new thread_arg_t[num_threads];

    // calculate thread load
    int load = rows / num_threads; 

    // create the threads
    for (int ii = 0; ii < num_threads; ++ii)
    {
        long double x, y;
        args[ii].num = (ii + 1);
        args[ii].image = image;
        args[ii].max_iters = max_iters;

        for (int row = (ii * load); row < (ii * load + load); ++row)
        {
            y = start_y + (end_y - start_y)/rows * row;
                    
            for (int col = 0; col < cols; ++col)
            {
                x = start_x + (end_x - start_x)/cols * col;

                args[ii].c.push_back(pair<long double, long double>(x, y));
                args[ii].pixel.push_back(pair<int,int>(row, col));
            }
        }
    }

    // start threads
    for (int ii = 0; ii < num_threads; ++ii)
    pthread_create(&args[ii].id, nullptr, ThreadedComputeMandelbrot, &args[ii]);

    // wait for threads to finish
    for (int ii = 0; ii < num_threads; ++ii)
    {
        pthread_join(args[ii].id, nullptr);
        printf("thread %d\tduration: %f sec\n", args[ii].num, args[ii].duration);
    }
            
    delete[] args;
}

// ******************************************************
// Generates the Mandelbrot set using a more balanced, 
// threaded computation
// Params:
//    Default values for command line args and a reference
//    to the image object
// Return:
//    none
void FasterThreadedApproach(int rows, int cols, long double start_x, long double end_x, long double start_y, 
                      long double end_y, int max_iters, int num_threads, Bmp_c *image)
{
    // create thread arg array
    thread_arg_t *args = new thread_arg_t[num_threads];

    // create the threads
    for (int ii = 0; ii < num_threads; ++ii)
    {
        long double x, y;
        args[ii].num = (ii + 1);
        args[ii].image = image;
        args[ii].max_iters = max_iters;
        
        for (int row = ii; row < rows; row += num_threads)
        {
            y = start_y + (end_y - start_y)/rows * row;
                    
            for (int col = 0; col < cols; ++col)
            {
                x = start_x + (end_x - start_x)/cols * col;

                args[ii].c.push_back(pair<long double, long double>(x, y));
                args[ii].pixel.push_back(pair<int,int>(row, col));
            }
        }
    }

    // start threads
    for (int ii = 0; ii < num_threads; ++ii)
        pthread_create(&args[ii].id, nullptr, ThreadedComputeMandelbrot, &args[ii]);

    // wait for threads to finish
    for (int ii = 0; ii < num_threads; ++ii)
    {
        pthread_join(args[ii].id, nullptr);
        printf("thread %d\tduration: %f sec\n", args[ii].num, args[ii].duration);
    }

    delete[] args;
}

// ******************************************************
// Generates the Mandelbrot set using provided approach
// Params:
//    Default values for command line args 
// Return:
//    none
void SimpleApproach(int rows, int cols, long double start_x, long double end_x, 
                    long double start_y, long double end_y, int max_iters, Bmp_c *image)
{
    long double x, y, value;

    // Loop through all points in the points in the image
    for (int row = 0; row < rows; ++row)
    {
        y = start_y + (end_y - start_y)/rows * row;

        for (int col = 0; col < cols; ++col)
        {
            x = start_x + (end_x - start_x)/cols * col;

            value = ComputeMandelbrot(x, y, max_iters);
            // set the pixel
            image->Set_Pixel(row, col, value);
        }
    }
}

// ******************************************************
// Calculates points for mandelbrot set for the number 
// of rows assigned (thread load)
// Params:
//    thread_arg_t* cast to void*
// Return:
//    none
void *ThreadedComputeMandelbrot(void *a)
{
    thread_arg_t *args = static_cast<thread_arg_t*>(a);
    
    clock_t start = clock();
    
    for (auto ii = 0; ii < (int)(args->c.size()); ++ii)
    {
        long double value = ComputeMandelbrot(args->c[ii].first, args->c[ii].second, args->max_iters);
        args->image->Set_Pixel(args->pixel[ii].first, args->pixel[ii].second, value);
    } 

    clock_t finish = clock();
    args->duration = ((float)(finish) - (float)(start))/CLOCKS_PER_SEC;

    return nullptr;
}

//*****************************************************
// Determine if a single point is in the mandelbrot set.
// Params:
//    (x,y): The complex number to make the determination on
//    max_iters: the maximum number of iterations to run
//
// Return:
//    zero if the number is in the set
//    number of iterations to conclude it's not in the set
int ComputeMandelbrot(long double x, long double y, int max_iters)
{
    complex<long double> c(x,y), z(0,0);

    for (int ii=0; ii<max_iters; ii++)
    {
        z = z*z + c;

        // if the magnitude goes above 2.0, it is guaranteed to blow up, so we
        // don't need to continue to compute
        if (std::abs(z) >= 2.0) return ii+1;
    }

    return 0;
}

//**************************************************
// choose a color for a particular mandelbrot value
// Params:
//     value: value returned by ComputeMandelbrot
//     max_value: the max value returned by ComputeMandelbrot
//                note: this is max_iters
// Return: 8 bit color value to be displayed
inline int ColorizeMono(int value, int max_value)
{
    if (value == 0)
        value = 255;
    else
        value = 0;

    return value;
}

//**************************************************
// choose a color for a particular mandelbrot value
// Params:
//     value: value returned by ComputeMandelbrot
//     max_value: the max value returned by ComputeMandelbrot
//                note: this is max_iters
// Return: 8 bit color value to be displayed
inline int ColorizeScaled(int value, int max_value)
{
    value = value*255/max_value*8;
    if (value > 255) value = 255;

    return value;
}

static const char *HELP_STRING = 
    "mandelbrot <options> where <options> can be the following\n"
    "   -h print this help string\n"
    "   -f use fast threaded algorithm\n"
    "   -F use faster threaded algorithm\n"
    "   -x <value> the starting x value. Defaults to -2\n"
    "   -X <value> the ending x value. Defaults to +2\n"
    "   -y <value> the starting y value. Defaults to -2\n"
    "   -Y <value> the ending y value. Defaults to +2\n"
    "   -r <value> the number of rows in the resulting image. Default 256.\n"
    "   -c <value> the number of cols in the resulting image. Default 256.\n"
    "   -m <value> the max number of iterations. Default is 1024.\n"
    "   -n <value> the number of threads to use. Default is 1.\n"
    "";

//*************************************************
// Main function to compute mandelbrot set image
// Command line args: See HELP_STRING above
//
// Note: the command line args are not sanity checked. You asked for it, 
//       you got it, even if the result is meaningless.
int main(int argc, char** argv)
{    
    // default values for command line args
    int max_iters = 1024;
    int num_threads = 1;
    int rows = 256;
    int cols = 256;
    long double start_x = -2.0;
    long double end_x = 2.0;
    long double start_y = -2.0;
    long double end_y = 2.0;
    algorithm mode = SIMPLE;
    int opt;

    // get command line args
    while ((opt = getopt(argc, argv, "fFhx:X:y:Y:r:c:m:n:")) >= 0)
    {
        switch (opt)
        {
            case 'x':
                sscanf(optarg, "%Lf", &start_x);
                break;
            case 'X':
                sscanf(optarg, "%Lf", &end_x);
                break;
            case 'y':
                sscanf(optarg, "%Lf", &start_y);
                break;
            case 'Y':
                sscanf(optarg, "%Lf", &end_y);
                break;
            case 'r':
                rows = atoi(optarg);
                break;
            case 'c':
                cols = atoi(optarg);
                break;
            case 'm':
                max_iters = atoi(optarg);
                break;
            case 'n':
                num_threads = atoi(optarg);
                break;
            case 'h':
                printf(HELP_STRING);
                return 0;
            case 'f':
                mode = THREADED;
                break;
            case 'F':
                mode = BALANCED;
                break;
            default:
                fprintf(stderr, HELP_STRING);
                return 0;
        }
    }

    // create and compute the image
    Bmp_c image(rows, cols);

    switch(mode)
    {
        case THREADED:
            printf("Computing with fast threaded approach.\n\n");
            FastThreadedApproach(rows, cols, start_x, end_x, start_y, end_y, max_iters, num_threads, &image);
            break;
        case BALANCED:
            printf("Computing with faster threaded approach.\n\n");
            FasterThreadedApproach(rows, cols, start_x, end_x, start_y, end_y, max_iters, num_threads, &image);
            break;
        default:
            printf("Computing with simple approach.\n");
            SimpleApproach(rows, cols, start_x, end_x, start_y, end_y, max_iters, &image);
            break;   
    }

    // define the pallet
    uint32_t pallet[256];
    for (int ii=0; ii<256; ii++)
    {
        pallet[ii] = Bmp_c::Make_Color(ii, 0, ii);
    }

    image.Set_Pallet(pallet);
    
    // create and write the output
    FILE *output = fopen("image.bmp", "wb");
    image.Write_File(output);
    fclose(output);

    printf("\nFile was written.\n");

    return 0;
}
