//
//  main.c
//  mod2
//
//  Created by Pablo Balmaceda Rescia on 17/12/2025.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void simulate_ising_model(int L, double T, int equilibration_steps, int measurement_steps, double result_array[5]);
void save_results(int L, int num_temperatures, const double *results_for_size, const char *filename);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    // Set random seed
       srand((unsigned int)time(NULL));
       
       // Simulation parameters
       int lattice_sizes[] = {8, 16, 32, 64};
       int num_sizes = sizeof(lattice_sizes) / sizeof(lattice_sizes[0]);
      
       // Este print no es parte del códigp oroginal
       printf("Número de lados = %d\n" , num_sizes);
       
       double T_min = 2.0;
       double T_max = 2.5;
       double T_step = 0.02;
       int num_temperatures = (int)((T_max - T_min) / T_step) + 1;
       
       int equilibration_steps = 10000;
       int measurement_steps = 50000;
       
       // Results storage
       double **results = malloc((unsigned long)num_sizes * sizeof(double *));
       for (int i = 0; i < num_sizes; i++) {
           results[i] = malloc((unsigned long)(num_temperatures * 5) * sizeof(double));
       }
       
       // Run simulations for different lattice sizes
       for (int size_idx = 0; size_idx < num_sizes; size_idx++) {
           int L = lattice_sizes[size_idx];
           printf("Simulating L= %d\n", L);
           
           for (int t_idx = 0; t_idx < num_temperatures; t_idx++) {
               double T = T_min + t_idx * T_step;
               double result_array[5];
               
               simulate_ising_model(L, T, equilibration_steps, measurement_steps, result_array);
               
               // Store results: T, M, chi, C, U4
               results[size_idx][t_idx * 5] = T;
               results[size_idx][t_idx * 5 + 1] = result_array[0]; // M
               results[size_idx][t_idx * 5 + 2] = result_array[1]; // chi
               results[size_idx][t_idx * 5 + 3] = result_array[2]; // C
               results[size_idx][t_idx * 5 + 4] = result_array[3]; // U4
               
               printf("T=%.3f, M=%.4f, chi=%.4f, C=%.4f, U4=%.4f\n",
                      T, result_array[0], result_array[1], result_array[2], result_array[3]);
           }
           
           // Save results for this lattice size to file
           char filename[50];
           // char path[50];
           sprintf(filename, "ising_results_L%d.dat", L);
           //printf("Archivo = %s\n", filename);
           printf("Archivo = %s\n", filename);
           //save_results(L, num_temperatures, results[size_idx], filename);
           save_results(L, num_temperatures, results[size_idx], filename);

       }
       
       // Free memory
       for (int i = 0; i < num_sizes; i++) {
           free(results[i]);
       }
       free(results);
       
    
    
    return EXIT_SUCCESS;
}

