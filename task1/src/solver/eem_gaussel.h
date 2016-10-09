void reduction(float ***matrix, int number_of_lines) {
  int i,j,k;
  int cnt=0;
  float pivot;

  //printf("\nGaussian elimination started:\n");
  for(i=0; i<number_of_lines-1; i++){
    for(j=i+1; j<number_of_lines; j++) {
      pivot = -(*matrix)[j][i] / (*matrix)[i][i];
	  for(k=i;k<number_of_lines+1;k++)
        (*matrix)[j][k] += (*matrix)[i][k]*pivot;
	}
	cnt++;
	//printf("\ngaussel line: %d", cnt);
  }
  //printf("\n\n");
}
