#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int local_min = INT_MAX;
    int array[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator
    srand(rank);

    // Generate random numbers for the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // Generate numbers between 0 and 999
    }

    // Find local minimum
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] < local_min) {
            local_min = array[i];
        }
    }

    // Find global minimum using MPI_Reduce
    int global_min;
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Output the result from process 0
    if (rank == 0) {
        printf("Minimum number: %d\n", global_min);
    }

    MPI_Finalize();

    return 0;
}
