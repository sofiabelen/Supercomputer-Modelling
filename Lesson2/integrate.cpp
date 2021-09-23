#include <stdio.h>

double BlackBoxFunction(double x);

double calc_int(double a, double b, int n) {
    const double dx = (b - a) / ((double) n);
    double integral = 0;

    for (int i = 0; i < n; i++) {
        const double xi = dx * ((double)i + 0.5) + a;
        const double dI = BlackBoxFunction(xi) * dx;
        integral += dI;
    }
    return integral;
}

int main() {
    double integral = calc_int(0, 1, 1e9);
    printf("Non-vectorized code\n");
    printf("Integral of blackbox: I = %f\n", integral);
    return 0;
}

double BlackBoxFunction(double x) {
    return 4.0 / (1.0 + x * x);
}
