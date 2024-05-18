#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main(int argc, char** argv) {
    double a[N][N], b[N][N], c[N][N];
    int i, j, k, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                a[i][j] = rand() % 100;
                b[i][j] = rand() % 100;
                c[i][j] = 0.0;
            }
        }
    }

    MPI_Bcast(a, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int local_n = N / size;
    int local_start = rank * local_n;
    int local_end = (rank + 1) * local_n;

    for (i = local_start; i < local_end; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    MPI_Reduce(c, c, N*N, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Multiplicação de matrizes concluída.\n");
    }


    return 0;
}
