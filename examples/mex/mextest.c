#include <time.h>
#include "mex.h"
#include <omp.h>

void compute(){
  unsigned long long siz = 100000000000;

  
  omp_set_dynamic(0);
  omp_set_num_threads(8);
  
  double start = omp_get_wtime();
  
  volatile unsigned long long counter = 0;
  static volatile unsigned long long tcounter = 0;
  #pragma omp threadprivate(tcounter)
  
    #pragma omp parallel for
    for(unsigned long long i = 0; i < siz; i++){
      tcounter++;
    }
  

  double end = omp_get_wtime();
  
  double time_elapsed = (end-start);
  
  counter = tcounter;
  mexPrintf("result: %llu, time elapsed: %f",counter,time_elapsed);
}

void mexFunction(int nlhs,mxArray* plhs[], int nrhs, const mxArray* prhs[]){
  compute();
#ifdef _OPENMP
  mexPrintf("Hej2");
  return;
#endif
  mexPrintf("Hej1");
}
