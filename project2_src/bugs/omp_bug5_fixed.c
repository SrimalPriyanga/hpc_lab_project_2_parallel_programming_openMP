
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main(int argc, char *argv[]) {
    int i, tid;
    float a[N], b[N], c[N];
    omp_lock_t locka, lockb;

    // Initialize locks
    omp_init_lock(&locka);
    omp_init_lock(&lockb);

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

    #pragma omp parallel private(i, tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            omp_set_lock(&locka);
            omp_set_lock(&lockb);
            for (i = 0; i < N; i++)
                a[i] = a[i] + b[i];
            omp_unset_lock(&lockb);
            omp_unset_lock(&locka);
        } else if (tid == 1) {
            omp_set_lock(&locka);
            omp_set_lock(&lockb);
            for (i = 0; i < N; i++)
                b[i] = a[i] + b[i];
            omp_unset_lock(&lockb);
            omp_unset_lock(&locka);
        }
    }

    // Destroy locks
    omp_destroy_lock(&locka);
    omp_destroy_lock(&lockb);

    printf("Completed successfully.\n");
    return 0;
}
