#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int data[ARRAY_SIZE];
    int local_max, global_max;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate random numbers
    srand(rank); // Seed based on rank to get different numbers for each process
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Find local maximum
    local_max = data[0];
    for (int i = 1; i < ARRAY_SIZE; i++) {
        if (data[i] > local_max) {
            local_max = data[i];
        }
    }

    // Use MPI_Reduce to find global maximum
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // Print result
    if (rank == 0) {
        printf("Global maximum: %d\n", global_max);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
