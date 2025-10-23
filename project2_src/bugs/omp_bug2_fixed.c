#include <omp.h>
#include <stdio.h>

int main() {
    int i;
    float total = 0.0;

    #pragma omp parallel for reduction(+:total) schedule(dynamic, 10)
    for (i = 0; i < 1000000; i++) {
        total += i * 1.0;
    }

    printf("Total = %e\n", total);
    return 0;
}
