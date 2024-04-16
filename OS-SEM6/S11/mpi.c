#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char **argv) {
    int rank, size;
    int local_min = RAND_MAX; // Initialize local_min with the maximum possible value
    int global_min;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator differently on each process
    srand(rank);

    // Generate 1000 random numbers and find the local minimum
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int num = rand();
        if (num < local_min) {
            local_min = num;
        }
    }

    // Use MPI_Reduce to find the global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Print the global minimum from rank 0
    if (rank == 0) {
        printf("Global minimum: %d\n", global_min);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
