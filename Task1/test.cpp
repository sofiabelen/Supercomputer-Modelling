#include <omp.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    omp_set_num_threads(48);
    int P = omp_get_max_threads();
    printf("%d\n", P);
    return 0;
}
