#include <omp.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<double> MatrixMultiply(int l, int m, int n,
        vector<double> A, vector<double> B);
vector<double> MatrixMultiplyParallel(int l, int m, int n,
        int P, vector<double> A, vector<double> B);
void ShowMatrix(int n, int m, vector<double> A);
double Analyse(int P, int N);

int main() {
    srand(time(nullptr));

    int l = 100, m = 100, n = 100;

    vector<double> A(l * m);
    vector<double> B(m * n);

    for (int j = 0; j < m; j++)
        for (int i = 0; i < l; i++)
            A[i + j * l] = (double)std::rand() / (double)RAND_MAX;

    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
            B[i + j * m] = (double)std::rand() / (double)RAND_MAX;

    double start = omp_get_wtime();
    vector<double> C  = MatrixMultiply(l, m, n, A, B);
    double t1 = omp_get_wtime() - start;

    start = omp_get_wtime();
    vector<double> C1 = MatrixMultiplyParallel(l, m, n, 8, A, B);
    double t2 = omp_get_wtime() - start;

    printf("Sequential: time = %f\n", t1);
    // ShowMatrix(l, n, C);
    printf("Parallel: time = %f\n", t2);
    // ShowMatrix(l, n, C1);

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
        int P, vector<double> A, vector<double> B) {

    vector<double> C(l * n, 0);

#pragma omp parallel for collapse(3) num_threads(P)
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < l; i++) {
            for (int k = 0; k < m; k++) {
                if (j == 0 && i == 0 && k == 0)
                    printf("nThreads: %d\n", omp_get_num_threads());
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
