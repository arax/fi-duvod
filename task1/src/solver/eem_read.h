void read_molecule(char *filename, atom ***atoms, int *number_of_atoms_r)
{
  char str[SIZE_STRING],str2[SIZE_STRING],str3[SIZE_STRING];
  char strl1[SIZE_STRING],strl2[SIZE_STRING];

  char chemical_symbol[SIZE_CHEMICAL_SYMBOL];
  int number_of_atoms, number_of_bonds;
  int i, proton_number;
  int atom1, atom2, multiplicity;
  int len, len1, len2, l, lcnt = 0;

  FILE *fr;

  fr=fopen(filename,"r");
  if(fr==NULL)
  {
    printf("\nERROR: Can not open file \"%s\".\n",filename);
    exit(1);
  }

  // Read a head of MOL file
  fgets(str,SIZE_STRING,fr);
  fgets(str,SIZE_STRING,fr);
  fgets(str,SIZE_STRING,fr);
  fscanf(fr,"%s%s",str,str2);
  //printf("\n%s %s\n", str, str2);

  // Read number of atoms and bonds
  number_of_atoms = atoi(str);
  (*number_of_atoms_r) = number_of_atoms;
  number_of_bonds = atoi(str2);
  //printf("\n%d %d\n", number_of_atoms, number_of_bonds);
  fgets(str,SIZE_STRING,fr);
  //printf("\nout: %s", str);
  
  // Allocate a field atoms
  (*atoms)=(atom **)malloc(number_of_atoms*sizeof(atom *));
  for(i=0;i<number_of_atoms;i++)
    (*atoms)[i]=(atom *)malloc(sizeof(atom));

  // Read data about atoms
  for (i=0;i<number_of_atoms;i++) {
    
	// Read x, y, z and element symbol
	fscanf(fr,"%s%s%s%s",str, str2, str3, chemical_symbol);
    //printf("\n%s %s %s %s\n", str, str2, str3, chemical_symbol);
	
	// Store x, y, z 
	(*atoms)[i]->x = atof(str);
    (*atoms)[i]->y = atof(str2);
	(*atoms)[i]->z = atof(str3);
	//printf("\n %f %f %f\n",(*atoms)[i]->x, (*atoms)[i]->y, (*atoms)[i]->z);
	
	// Get and store proton number
	//printf("\n %s\n", chemical_symbol);
	proton_number = get_proton_number(chemical_symbol);
	if(proton_number == SIZE_PROTON_NUMBER) {
		printf("ERROR: Incorrect chemical symbol: %s\n", chemical_symbol);
		exit (2);
	}
	(*atoms)[i]->proton_number = proton_number;
	//printf("\n%d",proton_number);

	// Set maximal multiplicity to 0
	(*atoms)[i]->max_multiplicity = 0;
	
	fgets(str,SIZE_STRING,fr);
  }

  // Read data about bonds
  for (i=0;i<number_of_bonds;i++) {
    
	// Read atom1, atom2 and multiplicity
	fscanf(fr,"%s%s%s",str, str2, str3);
	len = strlen(str);
	if (len > 4)
	{
		lcnt++;
		len1 = len /2;
		len2 = len - len1;
    	//printf("\n%s %d %d %d", str, len, len1, len2);
		for (l=0;l<len1;l++) {
			strl1[l]=str[l];
		}
		strl1[l]='\0';
		//printf("\n%d %s", l, strl1);

		for (l=0;l<len2;l++) {
			strl2[l]=str[l+len1];
		}
		//printf("\n%d %s", l, strl2);
		strl2[l]='\0';
		//printf("\n%d %s", l, strl2);

		//printf("\n%s %s %s", str, strl1, strl2);
		strcpy(str,strl1);
		strcpy(str3,str2);
        strcpy(str2,strl2);
		//printf("\n%s %s %s\n", str, str2, str3);
			
	}

    //printf("\n%s %s %s\n", str, str2, str3);
	atom1 = atoi(str);
	atom2 = atoi(str2);
	multiplicity = atoi(str3);
    //printf("\n%d %d %d\n", atom1, atom2, multiplicity);
	
	// Set maximal multiplicity of atom1
	if( (*atoms)[atom1-1]->max_multiplicity < multiplicity)
		(*atoms)[atom1-1]->max_multiplicity = multiplicity;

	// Set maximal multiplicity of atom2
	if( (*atoms)[atom2-1]->max_multiplicity < multiplicity)
		(*atoms)[atom2-1]->max_multiplicity = multiplicity;

	fgets(str,SIZE_STRING,fr);
  }

  fclose(fr);
}


void read_parameters(char *filename)
{
  char str[SIZE_STRING],str2[SIZE_STRING],str3[SIZE_STRING];
  char chemical_symbol[SIZE_CHEMICAL_SYMBOL];
  int i, j, proton_number;
  int max_multiplicity;
  float A, B;
  FILE *fr;

  fr=fopen(filename,"r");
  if(fr==NULL) {
    printf("\nERROR: Can not open file \"%s\".\n",filename);
    exit(1);
  }

  // Set parameters to NOT_DEFINED
  for(i=0;i<SIZE_PROTON_NUMBER;i++) {
    for(j=0;j<SIZE_MAX_MULTIPLICITY;j++){
	  A_param[i][j] = NOT_DEFINED;
	  B_param[i][j] = NOT_DEFINED;
	}
  }

  // Read kappa parameter
  if( fscanf(fr,"%s%s",str,str2)!= 2) {
	printf("\nERROR: Incorrect line with kappa parameter.\n");
	exit(2);
  }
  kappa = atof(str2);
  //printf("\nkappa: %f\n",kappa);

  // Read parameters A and B
  while( fscanf(fr,"%s%s%s%s",chemical_symbol,str,str2,str3)== 4 ) {
    //printf("\n%s %s %s %s",chemical_symbol,str,str2,str3);
	proton_number = get_proton_number(chemical_symbol);
    max_multiplicity = atoi(str);
    A = atof(str2);
    B = atof(str3);
	A_param[proton_number-1][max_multiplicity-1] = A;
	B_param[proton_number-1][max_multiplicity-1] = B;
    //printf("\n%d %d %f %f\n",proton_number, max_multiplicity, A, B);
    //printf("\n%f %f\n",A_param[proton_number-1][max_multiplicity-1],\
	//        B_param[proton_number-1][max_multiplicity-1]);
  }

  fclose(fr);
}


