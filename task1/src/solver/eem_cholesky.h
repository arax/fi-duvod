void reduction(float ***matrix, int number_of_lines) {
  int i,j,l;
  float diff,all;

  float **temp;
  float res;

  //Preparation of matrix
  (*matrix)[0][0]=sqrt(((double)(*matrix)[0][0]));

  for(j=1;j<number_of_lines;j++)
    (*matrix)[0][j]=(*matrix)[0][j]/(*matrix)[0][0];

  for(i=1;i<number_of_lines;i++) {
    for(j=0;j<number_of_lines;j++) {
      if(i>j)
	    (*matrix)[i][j]=0;
      else if(i<j){
	    diff=0;
	    for(l=0;l<=i-1;l++)
	      diff += (*matrix)[l][i]*(*matrix)[l][j];
  	    (*matrix)[i][j]=((*matrix)[i][j]-diff)/(*matrix)[i][i];
      }
      else {
	    diff=0;
	    for(l=0;l<=i-1;l++)
	      diff += (*matrix)[l][i]*(*matrix)[l][i];

	    if(i!=number_of_lines-1)
	      all=(*matrix)[i][i]-diff;
	    else
	      all=diff-(*matrix)[i][i];

	    (*matrix)[i][i]=sqrt(((double)all));
      }
    }
  }

  //Reduction
  temp=(float **)malloc((number_of_lines)*sizeof(float *));
  for(i=0;i<number_of_lines;i++)
    temp[i]=(float *)malloc((number_of_lines+1)*sizeof(float));

  for(i=0;i<number_of_lines;i++)
    for(j=0;j<number_of_lines;j++)
      temp[i][j]=(*matrix)[j][i];
  for(i=0;i<number_of_lines;i++)
    temp[i][number_of_lines]=(*matrix)[i][number_of_lines];

  for(i=0;i<number_of_lines;i++){
    res=0;
    for(j=0;j<=i-1;j++)
      res+=(*matrix)[j][number_of_lines]*temp[i][j];
    (*matrix)[i][number_of_lines]=(temp[i][number_of_lines]-res)/temp[i][i];
  }

  (*matrix)[number_of_lines-1][number_of_lines] *= -1;

  for(i=0;i<number_of_lines;i++)
    free((void *) temp[i]);
  free((void *)temp);

}

