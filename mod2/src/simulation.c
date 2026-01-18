#include <stdlib.h>
#include <math.h>
#include "lattice.h"
#include "measurements.h"


int metropolis_step(int **lattice, int L, double T, double *energy_change) {
    // Select a random spin
    int i = rand() % L;
    int j = rand() % L;
    
    // Calculate energy change if flipped
    int neighbors = lattice[(i+1)%L][j] + lattice[(i-1+L)%L][j] + 
                    lattice[i][(j+1)%L] + lattice[i][(j-1+L)%L];
    int spin = lattice[i][j];
    int delta_E = 2 * spin * neighbors;
    *energy_change = delta_E;
    
    // Metropolis condition
    if (delta_E <= 0 || (double)rand() / RAND_MAX < exp(-delta_E / T)) {
        lattice[i][j] = -spin;
        return 1; // Flip accepted
    }
    
    return 0; // Flip rejected
}

void simulate_ising_model(int L, double T, int equilibration_steps, int measurement_steps, double *results) {
    // Allocate memory for lattice
    int **lattice = allocate_lattice(L);
    
    // Initialize lattice with random configuration
    initialize_lattice(lattice, L, 0.0);
    
    // Equilibration phase
    double energy_change;
    for (int step = 0; step < equilibration_steps; step++) {
        metropolis_step(lattice, L, T, &energy_change);
    }
    
    // Measurement phase
    double sum_M = 0.0, sum_M2 = 0.0, sum_M4 = 0.0;
    double sum_E = 0.0, sum_E2 = 0.0;
    int accepted_flips = 0;
    
    for (int step = 0; step < measurement_steps; step++) {
        accepted_flips += metropolis_step(lattice, L, T, &energy_change);
        
        // Measure every 10 steps to reduce correlation
        if (step % 10 == 0) {
            double M = fabs(calculate_magnetization(lattice, L));
            double E = calculate_energy(lattice, L);
            
            sum_M += M;
            sum_M2 += M * M;
            sum_M4 += M * M * M * M;
            sum_E += E;
            sum_E2 += E * E;
        }
    }
    
    int num_measurements = measurement_steps / 10;
    double avg_M = sum_M / num_measurements;
    double avg_M2 = sum_M2 / num_measurements;
    double avg_M4 = sum_M4 / num_measurements;
    double avg_E = sum_E / num_measurements;
    double avg_E2 = sum_E2 / num_measurements;
    
    // Calculate physical quantities
    double N = L * L;
    double susceptibility = N * (avg_M2 - avg_M * avg_M) / T;
    double specific_heat = (avg_E2 - avg_E * avg_E) / (N * T * T);
    double binder_cumulant = 1.0 - avg_M4 / (3.0 * avg_M2 * avg_M2);
    
    results[0] = avg_M;
    results[1] = susceptibility;
    results[2] = specific_heat;
    results[3] = binder_cumulant;
    
    // Free memory
    free_lattice(lattice, L);
}