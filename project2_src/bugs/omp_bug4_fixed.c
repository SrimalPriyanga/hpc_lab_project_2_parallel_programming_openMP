
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1048

int main() {
    int i, j, tid, nthreads;
    double a[N][N];

    #pragma omp parallel shared(nthreads, a) private(i, j, tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);

        #pragma omp for
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                a[i][j] = tid + i + j;
            }
        }

        printf("Thread %d done.\n", tid);
    }

    return 0;
}
