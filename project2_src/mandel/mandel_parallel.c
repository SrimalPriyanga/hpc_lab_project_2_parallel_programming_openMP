#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "consts.h"
#include "pngwriter.h"
#include "walltime.h"

int main()
{
    int i, j, n;
    double x, y, x2, y2, cx, cy;
    long nTotalIterationsCount = 0;

    // Create PNG image
    png_data *pPng = png_create(IMAGE_WIDTH, IMAGE_HEIGHT);

    // Start timer
    double startTime = walltime();

// Parallelize outer loop using OpenMP
#pragma omp parallel for private(i, cx, cy, x, y, x2, y2, n) reduction(+ : nTotalIterationsCount)
    for (j = 0; j < IMAGE_HEIGHT; j++)
    {
        cy = MIN_Y + j * ((MAX_Y - MIN_Y) / IMAGE_HEIGHT);
        for (i = 0; i < IMAGE_WIDTH; i++)
        {
            cx = MIN_X + i * ((MAX_X - MIN_X) / IMAGE_WIDTH);
            x = 0.0;
            y = 0.0;
            x2 = x * x;
            y2 = y * y;
            n = 0;

            while ((x2 + y2 <= 4.0) && (n < MAX_ITERS))
            {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
                x2 = x * x;
                y2 = y * y;
                n++;
            }

            nTotalIterationsCount += n;

            int r = n % 256;
            int g = n % 256;
            int b = n % 256;
            png_plot(pPng, i, j, r, g, b);
        }
    }

    // End timer
    double endTime = walltime();
    double totalTime = endTime - startTime;

    // Generate unique filename
    int threads = omp_get_max_threads();
    char filename[100];
    sprintf(filename, "mandel_parallel_output/mandel_%dx%d_%dthreads.png", IMAGE_WIDTH, IMAGE_HEIGHT, threads);
    png_write(pPng, filename);

    // Print benchmark statistics
    long nPixels = IMAGE_WIDTH * IMAGE_HEIGHT;
    printf("Total time:                 %f seconds\n", totalTime);
    printf("Image size:                 %d x %d = %ld Pixels\n", IMAGE_WIDTH, IMAGE_HEIGHT, nPixels);
    printf("Total number of iterations: %ld\n", nTotalIterationsCount);
    printf("Avg. time per pixel:        %e seconds\n", totalTime / nPixels);
    printf("Avg. time per iteration:    %e seconds\n", totalTime / nTotalIterationsCount);
    printf("Iterations/second:          %e\n", nTotalIterationsCount / totalTime);
    printf("MFlop/s:                    %f\n", (nTotalIterationsCount * 8.0) / (totalTime * 1e6));

    return 0;
}
