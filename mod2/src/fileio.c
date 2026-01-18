#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

void save_results(int L, int num_temperatures, const double *results, const char *filename) {
    char path[512];
    snprintf(path, sizeof(path), "../data/%s", filename);

    // Ensure the ../data directory exists
    char dataDir[512];
    snprintf(dataDir, sizeof(dataDir), "../data");

    struct stat st = {0};
    if (stat(dataDir, &st) == -1) {
        if (mkdir(dataDir, 0777) != 0 && errno != EEXIST) {
            printf("Error: Could not create data directory at %s (errno=%d)\n", dataDir, errno);
            // return; // Uncomment to fail early
        }
    } else if (!S_ISDIR(st.st_mode)) {
        printf("Error: %s exists but is not a directory\n", dataDir);
        // return; // Uncomment to fail early
    }

    printf("save_results -> %s\n", path);

    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        printf("Error: Could not open file %s for writing\n", path);
        return;
    }
    
    fprintf(fp, "T\tM\tchi\tC\tU4\n");
    for (int t_idx = 0; t_idx < num_temperatures; t_idx++) {
        fprintf(fp, "%.3f\t%.6f\t%.6f\t%.6f\t%.6f\n", 
                results[t_idx * 5],
                results[t_idx * 5 + 1],
                results[t_idx * 5 + 2],
                results[t_idx * 5 + 3],
                results[t_idx * 5 + 4]);
    }
    fclose(fp);
    printf("Results saved to %s\n", path);
}
