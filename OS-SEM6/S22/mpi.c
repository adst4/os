#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int data[ARRAY_SIZE];
    int local_sum = 0, global_sum = 0;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate random numbers
    srand(rank); // Seed based on rank to get different numbers for each process
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Calculate local sum of odd numbers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (data[i] % 2 != 0) {
            local_sum += data[i];
        }
    }

    // Use MPI_Reduce to find global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print result
    if (rank == 0) {
        printf("Global sum of odd numbers: %d\n", global_sum);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
