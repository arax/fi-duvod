#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "eem_dfn.h"
#include "eem_read.h"
#include "eem_write.h"
#include "eem_matrix.h"

//#define CHOLESKY
#ifdef CHOLESKY
  #include "eem_cholesky.h"
#else
  #include "eem_gaussel.h"
#endif

int VERBOSE_MODE=0;

main(int argc, char *argv[]) {

  int number_of_atoms, i;

  char filename_molecule[SIZE_STRING], filename_parameters[SIZE_STRING], mol_charge[SIZE_STRING];

  atom **atoms;

  float **dist_matrix, **EEM_matrix, *charges, chi;

  //Read and check arguments
  if(argc!=4 && (argc==5 && !strcmp(argv[1],"-v"))==0)
  {
    printf("eem_solver: Insufficient arguments.\n");
    printf("Usage: eem_solver_proteins molecule.mol STO3G_eem.par charge\n");
    exit(1);
  }
  if(argc==4) {
    strcpy(filename_molecule,argv[1]);
	strcpy(filename_parameters,argv[2]);
	strcpy(mol_charge,argv[3]);
  }
  else
  {
    strcpy(filename_molecule,argv[2]);
	strcpy(filename_parameters,argv[3]);
	strcpy(mol_charge,argv[4]);
    VERBOSE_MODE=1;
  }

  //Title of output
  printf("*************");
  printf("\nEEM SOLVER:");
  printf("\n*************");

  //Read molecule
  read_molecule(filename_molecule, &atoms, &number_of_atoms);
  if(VERBOSE_MODE == 1)
    write_atoms(atoms, number_of_atoms);

  //Read parameters
  read_parameters(filename_parameters);
  if(VERBOSE_MODE == 1)
    write_parameters();

  //Calculate distance matrix
  calculate_dist_matrix(&dist_matrix, number_of_atoms, atoms);
  if(VERBOSE_MODE == 1)
    write_matrix(dist_matrix, number_of_atoms, number_of_atoms, "Distance matrix");

  //Create EEM matrix
  create_EEM_matrix(&EEM_matrix, dist_matrix, number_of_atoms, atoms, mol_charge);
  if(VERBOSE_MODE == 1)
    write_matrix(EEM_matrix, number_of_atoms+1, number_of_atoms+2, "EEM matrix");

  //Do Gaussian elimination
  //  Reduction of matrix 
  reduction(&EEM_matrix,number_of_atoms+1);
  if(VERBOSE_MODE == 1)
    write_matrix(EEM_matrix, number_of_atoms+1, number_of_atoms+2, "EEM matrix reduced");
  //  Back substitution   
  back_substitution(EEM_matrix,&charges,number_of_atoms+1,&chi);
 
  //Write results
  write_charges_chi(charges, number_of_atoms, atoms, chi);

  //Free allocated memory
  for(i=0;i<number_of_atoms;i++)
    free((void *) atoms[i]);
  free((void *) atoms);

  for(i=0;i<number_of_atoms;i++)
    free((void *)dist_matrix[i]);
  free((void *)dist_matrix);

  for(i=0;i<number_of_atoms+1;i++)
    free((void *) EEM_matrix[i]);
  free((void *)EEM_matrix);

  free((void *)charges);

}
