#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000
#define CHUNK 100

int main() {
    int i;
    float a[N], b[N], c[N];
    int chunk = CHUNK;
    int tid;

    for (i = 0; i < N; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

    #pragma omp parallel for shared(a, b, c, chunk) private(i, tid) schedule(static, chunk)
    for (i = 0; i < N; i++) {
        tid = omp_get_thread_num();
        c[i] = a[i] + b[i];
        printf("tid= %d i= %d c[i]= %f\n", tid, i, c[i]);
    }

    return 0;
}
