#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int odd_sum = 0;
    int array[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator
    srand(rank);

    // Generate random numbers for the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100; // Generate numbers between 0 and 99
    }

    // Calculate sum of odd numbers in the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] % 2 != 0) {
            odd_sum += array[i];
        }
    }

    // Sum up the results from all processes
    int global_odd_sum;
    MPI_Reduce(&odd_sum, &global_odd_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Output the result from process 0
    if (rank == 0) {
        printf("Sum of all odd numbers: %d\n", global_odd_sum);
    }

    MPI_Finalize();

    return 0;
}
