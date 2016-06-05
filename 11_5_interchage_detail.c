void multiply_matrices()
{
  int i, j, k ;

  // Loop nest interchange algorithm
  for (i = 0 ; i < MSIZE ; i++) {
    for (k = 0 ; k < MSIZE ; k++) {
      for (j = 0 ; j < MSIZE ; j++) {
        matrix_r[i][j] = matrix_r[i][j] +
          (matrix_a[i][k] * matrix_b[k][j]) ;
      }
    }
  }
}
