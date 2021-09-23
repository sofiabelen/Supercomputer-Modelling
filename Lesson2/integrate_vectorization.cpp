#include <omp.h>
#include <stdio.h>

// We tell the compiler to create a vectorized version
// of our function
#pragma omp declare simd
double BlackBoxFunction(double x);
double calc_int(double a, double b, int n);

int main() {
    double integral = calc_int(0, 1, 1e9);
    printf("Vectorized code\n");
    printf("Integral of blackbox: I = %f\n", integral);
    return 0;
}

double BlackBoxFunction(double x) {
    return 4.0 / (1.0 + x * x);
}

double calc_int(double a, double b, int n) {
    const double dx = (b - a) / ((double) n);
    double integral = 0;

// Reduction is when you accumulate a value during a loop.
// We use this pragma to vectorize the reduction loop.
#pragma omp simd reduction(+: integral)
    for (int i = 0; i < n; i++) {
        const double xip12 = dx * ((double)i + 0.5) + a;
        const double dI = BlackBoxFunction(xip12) * dx;
        integral += dI;
    }
    return integral;
}
