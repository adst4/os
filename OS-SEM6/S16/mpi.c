#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char** argv) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_min, global_min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Generate random numbers
    srand(rank + 1);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 1000;
    }

    // Find local minimum
    local_min = numbers[0];
    for (int i = 1; i < ARRAY_SIZE; i++) {
        if (numbers[i] < local_min) {
            local_min = numbers[i];
        }
    }

    // Reduce local minimums to global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global minimum number: %d\n", global_min);
    }

    MPI_Finalize();

    return 0;
}
