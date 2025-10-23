
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main (int argc, char *argv[]) {
    int i, tid, section;
    float a[N], b[N], c[N];

    for (i = 0; i < N; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

    #pragma omp parallel shared(c) private(i, tid, section)
    {
        tid = omp_get_thread_num();

        #pragma omp sections
        {
            #pragma omp section
            {
                section = 1;
                for (i = 0; i < N; i++)
                    c[i] = a[i] + b[i];
                printf("Thread %d did section %d\n", tid, section);
            }

            #pragma omp section
            {
                section = 2;
                for (i = 0; i < N; i++)
                    c[i] = a[i] * b[i];
                printf("Thread %d did section %d\n", tid, section);
            }
        }
    }

    printf("Done.\n");
    return 0;
}
