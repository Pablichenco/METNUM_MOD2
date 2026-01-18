#ifndef LATTICE_H
#define LATTICE_H

// Function declarations
int** allocate_lattice(int L);
void initialize_lattice(int **lattice, int L, double initial_magnetization);
void free_lattice(int **lattice, int L);

#endif