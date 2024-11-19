#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {

   #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      // printf("my_dgemv(): Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
      // printf("my_dgemv(): For actual timing runs, please comment out these printf() and omp_get_*() statements. \n");
   }

   // insert your dgemv code here. you may need to create additional parallel regions,
   // and you will want to comment out the above parallel code block that prints out
   // nthreads and thread_id so as to not taint your timings
   #pragma omp parallel for   // parallel with workshare, each parallel code has a different i
   for (int i = 0; i < n; i++) {
        // reset the total sum for each new row being calculated
        double rowSum = 0.0;
        // no reduction needed here as each parallel code has its own rowSum
        for (int j = 0; j < n; j++) {
            // add A[i,j] * x[j] for each col of A in current row i
            rowSum += A[i * n + j] * x[j]; 
        }
        // add the total sum of col products in the corresponding row of y
        // could also just be "y[i] = rowSum;" if "Y :=  A * X" was specified instead of "Y :=  A * X + Y"
        y[i] += rowSum;
    }

}

