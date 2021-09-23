#include <omp.h>
#include <time.h>
#include <stdio.h>

int main() {
    const int n = 10000;
    double array[n], sum[4];
    double start, end, sum1 = 0;
    size_t nthreads;

    for (int i = 0; i < n; i++) {
        array[i] = i;
    }

    for (int i = 0; i < 4; i++) {
        sum[i] = 0;
    }

    start = omp_get_wtime();
    for (int i = 0; i < n; i++) {
        sum1 += array[i];
    }
    end = omp_get_wtime();

    printf("Array sum: %f\n", sum1);
    printf("Elapsed time: %lfs\n", end - start);


    start = omp_get_wtime();
#pragma omp parallel
    {
        int nthrds = omp_get_num_threads();
        int tid = omp_get_thread_num();

        if (tid == 0)
            nthreads = nthrds;

        for (int i = tid; i < n; i += nthrds) {
            sum[tid] += array[i];
        }
        end = omp_get_wtime();
    }

    for (int i = 1; i < nthreads; i++)
        sum[0] += sum[i];

    end = omp_get_wtime();

    printf("Array sum: %f\n", sum[0]);
    printf("Elapsed time: %lfs\n", end - start);
    
    return 0;
}
