void write_atoms(atom **atoms, int number_of_atoms)
{
  int i;

  printf("\nAtoms:");
  printf("\n  Index  | Prot.n. | Chem.s. | Max.m. |     X    |     Y    |     Z    |");
  for(i=0;i<number_of_atoms;i++) {
    printf("\n  %4d   |",i+1);
    printf("   %3d   |",atoms[i]->proton_number);
    printf("   %2s    |", periodic_table[(atoms[i]->proton_number)-1]);
    printf("    %d   |",atoms[i]->max_multiplicity);
    printf("  % 3.3f  |",atoms[i]->x);
    printf("  % 3.3f  |",atoms[i]->y);
    printf("  % 3.3f  |",atoms[i]->z);
  }
  printf("\n");
}

void write_parameters()
{
  int i,j;

  printf("\nParameters:");
  printf("\nKappa: % 3.4f", kappa);
  printf("\nA and B:");
  printf("\n Chem.s. | Max.m. |     A     |     B     |\n");
  for(j=0;j<SIZE_MAX_MULTIPLICITY;j++){
	for(i=0;i<SIZE_PROTON_NUMBER;i++) {
	  if(A_param[i][j]!=NOT_DEFINED || B_param[i][j]!=NOT_DEFINED) {
        printf("    %2s   |", periodic_table[i]);
        printf("    %d   |", j+1);
        printf("  % 3.4f  |", A_param[i][j]);
        printf("  % 3.4f  |", B_param[i][j]); 
		printf("\n");
	  }
	}
  }
  printf("\n");
}


void write_matrix(float **matrix, int row, int column, char *description)
{
  int i,j;

  printf("%s:\n", description);
  for(i=0;i<row;i++) {
    for(j=0;j<column;j++)
      printf(" % 3.4f ",matrix[i][j]);
    printf("\n");
  }
  printf("\n");
}

void write_charges_chi(float *charges, int number_of_atoms, atom **atoms, float chi)
{
  int i;

  printf("\n\nATOMIC CHARGES:");
  printf("\n  Index  | Chem.s. |   Charge   |\n");
  for(i=0;i<number_of_atoms;i++)
    printf("   %3d   |   %2s    |  % 3.4f   |\n",i+1, periodic_table[(atoms[i]->proton_number)-1], charges[i]);
  printf("\nMOLECULAR ELECTRONEGATIVITY:\n");
  printf("  % 3.4f\n\n",chi);
}
