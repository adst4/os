#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int sum = 0;
    double average;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        srand(0);
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            numbers[i] = rand() % 1000;
        }
    }

    MPI_Scatter(numbers, ARRAY_SIZE / size, MPI_INT, numbers, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    for (int i = 0; i < ARRAY_SIZE / size; ++i) {
        local_sum += numbers[i];
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        average = (double)sum / ARRAY_SIZE;
        printf("Sum: %d\n", sum);
        printf("Average: %lf\n", average);
    }

    MPI_Finalize();
    return 0;
}
