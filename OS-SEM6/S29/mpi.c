#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int array[ARRAY_SIZE];
    int local_sum = 0, global_sum = 0;

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

    // Calculate local sum of even numbers
    for (int i = rank; i < ARRAY_SIZE; i += size) {
        if (array[i] % 2 == 0) {
            local_sum += array[i];
        }
    }

    // Reduce the local sums to obtain the global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result
    if (rank == 0) {
        printf("Global sum of even numbers: %d\n", global_sum);
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
