#include "lattice.h"

double calculate_energy(int **lattice, int L) {
    double energy = 0.0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            int spin = lattice[i][j];
            int neighbors = lattice[(i+1)%L][j] + lattice[(i-1+L)%L][j] +
                            lattice[i][(j+1)%L] + lattice[i][(j-1+L)%L];
            energy -= spin * neighbors; // Energy calculation
        }
    }
    return energy / 2.0; // Each pair is counted twice
}

double calculate_magnetization(int **lattice, int L) {
    double magnetization = 0.0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            magnetization += lattice[i][j];
        }
    }
    return magnetization / (L * L); // Normalize by the number of spins
}