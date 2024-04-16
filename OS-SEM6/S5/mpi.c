#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int max_local = 0;
    int max_global = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        srand(0);
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            numbers[i] = rand();
        }
    }

    MPI_Scatter(numbers, ARRAY_SIZE / size, MPI_INT, numbers, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < ARRAY_SIZE / size; ++i) {
        if (numbers[i] > max_local) {
            max_local = numbers[i];
        }
    }

    MPI_Reduce(&max_local, &max_global, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Maximum number: %d\n", max_global);
    }

    MPI_Finalize();
    return 0;
}
