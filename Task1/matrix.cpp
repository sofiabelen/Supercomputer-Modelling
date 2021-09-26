#include <omp.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<double> MatrixMultiply(int l, int m, int n,
        vector<double> A, vector<double> B);
vector<double> MatrixMultiplyParallel(int l, int m, int n,
        vector<double> A, vector<double> B);
void ShowMatrix(int n, int m, vector<double> A);
double Analyse(int P, int N);

int main() {
    srand(time(nullptr));

    vector<int> P {1, 2, 4, 8, 16, 24, 32, 40, 48};
    vector<int> N {500, 1000, 1500};

    for (int i = 0; i < P.size(); i++) {
        for (int j = 0; j < N.size(); j++) {
            double time = Analyse(P[i], N[j]);
            printf("%f ", time);
        }
        printf("\n");
    }
    printf("\n");

    // ShowMatrix(l, m, A);
    // ShowMatrix(m, n, B);
    // ShowMatrix(l, n, C);
    // ShowMatrix(l, n, C1);

    // printf("Time Sequential: %f\n", time1);
    // printf("Time Parallel:   %f\n", time2);

    return 0;
}

vector<double> MatrixMultiply(int l, int m, int n,
        vector<double> A, vector<double> B) {

    vector<double> C(l * n, 0);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < l; i++) {
            for (int k = 0; k < m; k++) {
                C[i + j * l] += A[i + k * l] * B[k + j * m];
            }
        }
    }

    return C;
}

vector<double> MatrixMultiplyParallel(int l, int m, int n,
        vector<double> A, vector<double> B) {

    vector<double> C(l * n, 0);

#pragma omp parallel for collapse(3) 
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < l; i++) {
            for (int k = 0; k < m; k++) {
                C[i + j * l] += A[i + k * l] * B[k + j * m];
            }
        }
    }

    return C;
}

void ShowMatrix(int n, int m, vector<double> A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%.2f ", A[i + j * n]);
        printf("\n");
    }
    printf("\n");
}

double Analyse(int P, int N) {
    omp_set_num_threads(P);

    int l = N, m = N, n = N;
    vector<double> A(l * m);
    vector<double> B(m * n);

    for (int j = 0; j < m; j++)
        for (int i = 0; i < l; i++)
            A[i + j * l] = (double)std::rand() / (double)RAND_MAX;

    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
            B[i + j * m] = (double)std::rand() / (double)RAND_MAX;

    double start = omp_get_wtime();
    vector<double> C = MatrixMultiplyParallel(l, m, n, A, B);
    double end = omp_get_wtime();

    return (end - start);
}
