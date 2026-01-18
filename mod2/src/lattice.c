#include <stdlib.h>
#include <stdio.h>

int** allocate_lattice(int L) {
    int **lattice = malloc(L * sizeof(int *));
    for (int i = 0; i < L; i++) {
        lattice[i] = malloc(L * sizeof(int));
    }
    return lattice;
}

void free_lattice(int **lattice, int L) {
    for (int i = 0; i < L; i++) {
        free(lattice[i]);
    }
    free(lattice);
}

void initialize_lattice(int **lattice, int L, double initial_magnetization) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            if ((double)rand() / RAND_MAX < (1.0 + initial_magnetization) / 2.0) {
                lattice[i][j] = 1;
            } else {
                lattice[i][j] = -1;
            }
        }
    }
}