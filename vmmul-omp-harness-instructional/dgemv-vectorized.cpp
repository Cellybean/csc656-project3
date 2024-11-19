const char* dgemv_desc = "Vectorized implementation of matrix-vector multiply.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */
void my_dgemv(int n, double* A, double* x, double* y) {
   // insert your code here: implementation of vectorized vector-matrix multiply
   for (int i = 0; i < n; i++) {
        // reset the total sum for each new row being calculated
        double rowSum = 0.0;
        for (int j = 0; j < n; j++) {
            // add A[i,j] * x[j] for each col of A in current row i
            rowSum += A[i * n + j] * x[j]; 
        }
        // add the total sum of col products in the corresponding row of y
        // could also just be "y[i] = rowSum;" if "Y :=  A * X" was specified instead of "Y :=  A * X + Y"
        y[i] += rowSum;
    }
}
