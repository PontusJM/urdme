omp_link = '-lgomp';
link = {omp_link ['-L' path] ['-L' path '../']};
mex('mextest.c',['CFLAGS= -fPIC -lgomp -fopenmp -std=c99 -D_GNU_SOURCE -pthread -fexceptions -fno-omit-frame-pointer -O0'], link{:});
feval('mextest');