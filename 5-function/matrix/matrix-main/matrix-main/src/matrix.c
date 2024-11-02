#include "matrix.h"
void matrix_multiply(int A[][MAX_SIZE],int B[][MAX_SIZE], int C[][MAX_SIZE],  int m, int n, int p){
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < p; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];  
}