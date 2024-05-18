#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    int n = 1000; 
    int *a = (int*) malloc(n * sizeof(int));
    int i, count = 0, total_count = 0, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (i = 0; i < n; i++) {
            a[i] = rand() % 100;
        }
    }

    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);

    int local_n = n / size;
    int local_start = rank * local_n;
    int local_end = (rank + 1) * local_n;

    for (i = local_start; i < local_end; i++) {
        if (a[i] % 2 == 0) {
            count++;
        }
    }

    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    return 0;
}
