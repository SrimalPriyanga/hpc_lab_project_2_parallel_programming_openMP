#include <iostream>
#include <omp.h>
#include <random>
#include <vector>
#include "walltime.h"

#define VEC_SIZE 1000000000
#define BINS 16

int main() {
    double time_start, time_end;

    // Initialize random number generator
    unsigned int seed = 123;
    float mean = BINS / 2.0;
    float sigma = BINS / 12.0;
    std::default_random_engine generator(seed);
    std::normal_distribution<float> distribution(mean, sigma);

    // Generate random sequence
    std::vector<int> vec(VEC_SIZE);
    for (long i = 0; i < VEC_SIZE; ++i) {
        vec[i] = int(distribution(generator));
        if (vec[i] < 0) vec[i] = 0;
        if (vec[i] > BINS - 1) vec[i] = BINS - 1;
    }

    // Initialize global histogram
    long dist[BINS] = {0};

    // Start timing
    time_start = walltime();

    // Parallel histogram computation
    int num_threads = omp_get_max_threads();
    std::vector<std::vector<long>> local_dists(num_threads, std::vector<long>(BINS, 0));

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        std::vector<long>& local = local_dists[tid];

        #pragma omp for
        for (long i = 0; i < VEC_SIZE; ++i) {
            local[vec[i]]++;
        }
    }

    // Merge local histograms into global histogram
    for (int t = 0; t < num_threads; ++t) {
        for (int b = 0; b < BINS; ++b) {
            dist[b] += local_dists[t][b];
        }
    }

    // End timing
    time_end = walltime();

    // Write results
    for (int i = 0; i < BINS; ++i) {
        std::cout << "dist[" << i << "]=" << dist[i] << std::endl;
    }
    std::cout << "Time: " << time_end - time_start << " sec" << std::endl;

    return 0;
}