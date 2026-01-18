#ifndef SIMULATION_H
#define SIMULATION_H

// Function declarations
int metropolis_step(int **lattice, int L, double T, double *energy_change);
void simulate_ising_model(int L, double T, int equilibration_steps, 
                         int measurement_steps, double *results);

#endif

