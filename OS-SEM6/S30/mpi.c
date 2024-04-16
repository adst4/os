#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int array[ARRAY_SIZE];
    int local_min = INT_MAX, global_min;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator
    srand(rank);

    // Generate random numbers for the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand();
    }

    // Calculate local minimum
    for (int i = rank; i < ARRAY_SIZE; i += size) {
        if (array[i] < local_min) {
            local_min = array[i];
        }
    }

    // Reduce the local minimums to obtain the global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Print the result
    if (rank == 0) {
        printf("Global minimum number: %d\n", global_min);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
