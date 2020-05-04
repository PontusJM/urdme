#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
  int sum = 0;
#if defined(_OPENMP)
  printf("openMp defined");
#endif

  omp_set_nested(true);
  omp_set_dynamic(false);
  
#pragma omp parallel for collapse(2) num_threads(2)
  for(int i = 0; i < 10000; i++){
    for(int j = 0; j < 10000; j++){
      printf("%d, %d thread id: %d\n",i,j,omp_get_thread_num());
    }
  }
  printf("sum: %d", sum);
}
