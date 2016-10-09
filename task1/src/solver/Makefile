TARGET_BINARY=eem_solver_proteins
COMPILER_BINARY=/usr/bin/gcc

all: solver

solver: eem_solver_proteins.c
	${COMPILER_BINARY} -o ${TARGET_BINARY} eem_solver_proteins.c -lm

clean:
	-rm ${TARGET_BINARY}
