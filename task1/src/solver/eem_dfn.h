#define SIZE_MAX_MULTIPLICITY 3
#define SIZE_PROTON_NUMBER 110
#define SIZE_STRING 255
#define NOT_DEFINED -1

#define EEM_SOLVER

#include "eem_p_table.h"

float kappa;

typedef struct {
   int proton_number;
   int max_multiplicity;
   float x;
   float y;
   float z;
} atom;

float A_param[SIZE_PROTON_NUMBER][SIZE_MAX_MULTIPLICITY];
float B_param[SIZE_PROTON_NUMBER][SIZE_MAX_MULTIPLICITY];




