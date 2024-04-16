#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char **argv) {
    int rank, size;
    int local_sum = 0;
    double local_average, global_sum, global_average;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator differently on each process
    srand(rank);

    // Generate 1000 random numbers and calculate local sum
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_sum += rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Calculate local average
    local_average = (double)local_sum / ARRAY_SIZE;

    // Use MPI_Reduce to find global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Use MPI_Reduce to find global average
    MPI_Reduce(&local_average, &global_average, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print results from rank 0
    if (rank == 0) {
        printf("Total sum: %.2f\n", global_sum);
        printf("Average: %.2f\n", global_average / size); // Calculate average across all processes
    }

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
