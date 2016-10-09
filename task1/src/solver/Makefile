TARGET_BINARY=eem_solver_proteins
CC=gcc

all: solver

solver: eem_solver_proteins.c
	${CC} -o ${TARGET_BINARY} eem_solver_proteins.c -lm 2>&1 1>/dev/null

clean:
	-rm ${TARGET_BINARY}
