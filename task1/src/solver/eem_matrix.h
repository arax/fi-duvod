void calculate_dist_matrix(float ***dist_matrix, int number_of_atoms, atom **atoms) {

  int i, j;
  float length_pow2;

  //Allocate field for distances (between atoms)
  (*dist_matrix)=(float ***)malloc(number_of_atoms*sizeof(float **));
  for(i=0;i<number_of_atoms;i++)
    (*dist_matrix)[i]=(float **)malloc(number_of_atoms*sizeof(float *));

  //Fill field of distances (between atoms)
  for(i=0;i<number_of_atoms;i++)
 	for(j=0;j<number_of_atoms;j++) {
	  length_pow2 = (atoms[i]->x - atoms[j]->x)*(atoms[i]->x - atoms[j]->x) + \
					(atoms[i]->y - atoms[j]->y)*(atoms[i]->y - atoms[j]->y) + \
					(atoms[i]->z - atoms[j]->z)*(atoms[i]->z - atoms[j]->z);

      (*dist_matrix)[i][j] = sqrt(((double)length_pow2));
	}
}

void create_EEM_matrix(float ***EEM_matrix, float **dist_matrix, int number_of_atoms, atom **atoms, char *mol_charge) {

  int i, j;
  float param;

  //Allocate field for EEM_matrix
  (*EEM_matrix)=(float ***)malloc((number_of_atoms+1)*sizeof(float **));
  for(i=0;i<number_of_atoms+1;i++)
    (*EEM_matrix)[i]=(float **)malloc((number_of_atoms+2)*sizeof(float *));

  //Fill EEM_matrix field
  for(i=0;i<number_of_atoms;i++)
  {
    for(j=0;j<number_of_atoms;j++)
    {
	  if(i==j) {
		param=B_param[atoms[i]->proton_number-1][atoms[i]->max_multiplicity-1];
        if(param==NOT_DEFINED) {
		  printf("ERROR: Parameter B for atom %s with max. multiplicity %d is not defined.\n",\
                  periodic_table[(atoms[i]->proton_number)-1],atoms[i]->max_multiplicity);
		  exit(3);
		}
		else
	      (*EEM_matrix)[i][j]=param;
      }
	  else
	    (*EEM_matrix)[i][j]=kappa/dist_matrix[i][j];
    }
  }

  for(i=0;i<number_of_atoms;i++)
    (*EEM_matrix)[number_of_atoms][i]=1;

  for(i=0;i<number_of_atoms;i++)
    (*EEM_matrix)[i][number_of_atoms]=-1;

  for(i=0;i<number_of_atoms;i++)
    (*EEM_matrix)[i][number_of_atoms+1]=-A_param[atoms[i]->proton_number-1][atoms[i]->max_multiplicity-1];

  (*EEM_matrix)[number_of_atoms][number_of_atoms]=0;
  (*EEM_matrix)[number_of_atoms][number_of_atoms+1]=atof(mol_charge);;

}

void back_substitution(float **matrix, float **charges, int number_of_lines, float *chi)
{
  int i,j;
  float res, *temp;
  
  //Allocate field for results
  (*charges)=(float **)malloc((number_of_lines-1)*sizeof(float *));

  //Allocate temporary field for results
  temp=(float *)malloc((number_of_lines)*sizeof(float));

  //Do back substitution
  for(i=number_of_lines-1;i>=0;i--)
  {
    res=0;
    for(j=i+1;j<number_of_lines;j++)
      res+=matrix[i][j]*temp[j];
    temp[i]=(matrix[i][number_of_lines]-res)/matrix[i][i];
  }

  //Move results from temp to charges and chi
  for(i=0;i<number_of_lines-1;i++)
	  (*charges)[i]=temp[i];
  (*chi)=temp[number_of_lines-1];

  //Free temp file
  free((void *)temp);

}
