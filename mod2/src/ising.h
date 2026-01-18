#ifndef ISING_H
#define ISING_H

// Function declarations
void initialize_lattice(int **lattice, int L, double initial_magnetization);
double calculate_energy(int **lattice, int L);
double calculate_magnetization(int **lattice, int L);
int** allocate_lattice(int L);
void free_lattice(int **lattice, int L);
void save_results(int L, int num_temperatures, double *results, char *filename);


#endif