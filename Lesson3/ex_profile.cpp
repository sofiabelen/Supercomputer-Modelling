#include <omp.h>
#include <stdio.h>

using namespace std;

void exec (double *a, double &sum, long N, int threads);

int main() {
    for (int threads = 2; threads <= 8; threads+=2) {
        exec(a, sum, N, threads);
    }
    return 0;
}

void exec (double *a, double &sum, long N, int threads) {
    double start, end;
    
    omp_set_num_threads (threads);
    printf("Threads = %d\n", threads);

    sum = 0;
    start = omp_get_wtime();
    critical (a, sum, N);
    end = omp_get_wtime();

    printf("Critical: \n Time = %f Sum = %f \n", end - strt, sum);

    sum = 0;
        start = omp_get_wtime();
    reduction (a, sum, N);
    end = omp_get_wtime();

    printf("Reduction: \n Time = %f Sum = %f\n\n", end -start, sum);
}
