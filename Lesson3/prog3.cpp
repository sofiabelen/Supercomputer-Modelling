#include <stdio.h>
#include <omp.h>
#define type_ float


int BlackBoxFunction (type_ x) {
  return (4. / (1. + x * x));
}

int main() {

  type_ Integral = 0., dI = 0., x; 
  int n = 100000000, nThreads = 8;
  double t_start, t_diff;
  const type_ dx = (1. - 0.) / (type_) n;

  for (nThreads = 1; nThreads < 10; nThreads++) {
    Integral = 0.;
    t_start = omp_get_wtime();
//    #pragma omp parallel for num_threads(nThreads) reduction(+: Integral)
    
//   #pragma omp simd reduction(+: Integral)
#pragma omp parallel for num_threads(nThreads) reduction(+: Integral)
    for (int i = 1; i < n; i++) { 
          x = ( (type_) i - 0.5 ) / (type_) n;
          dI = BlackBoxFunction( x ) / (type_) n;
          Integral += dI;
    }
    t_diff = omp_get_wtime() - t_start;
    printf("Integral = %lf \n nThreads = %d \n t_diff = %lf \n", Integral, nThreads,  t_diff);
  }
 //}
  return 0;
}
