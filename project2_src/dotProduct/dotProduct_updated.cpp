
#include <iostream>
#include <omp.h>
#include "walltime.h"

int main() {
    const int N = 1000000;
    const int NUM_ITERATIONS = 10;
    double *a = new double[N];
    double *b = new double[N];
    double alpha_parallel = 0.0;
    double time_start, time_red, time_critical;

    // Initialize vectors
    for (int i = 0; i < N; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
    }

    // Reduction version
    time_start = wall_time();
    for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
        alpha_parallel = 0.0;
        #pragma omp parallel for reduction(+:alpha_parallel)
        for (int i = 0; i < N; i++) {
            alpha_parallel += a[i] * b[i];
        }
    }
    time_red = wall_time() - time_start;
    std::cout << "Method: Reduction, Threads: " << omp_get_max_threads()
              << ", Time (s): " << time_red << std::endl;

    // Critical version
    time_start = wall_time();
    for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
        alpha_parallel = 0.0;
        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            double temp = a[i] * b[i];
            #pragma omp critical
            alpha_parallel += temp;
        }
    }
    time_critical = wall_time() - time_start;
    std::cout << "Method: Critical, Threads: " << omp_get_max_threads()
              << ", Time (s): " << time_critical << std::endl;

    delete[] a;
    delete[] b;
    return 0;
}
