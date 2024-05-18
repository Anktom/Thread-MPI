
#include <stdio.h>
#include <mpi.h>

#define N 1000  // Tamanho do vetor

int main(int argc, char *argv[]) {
    int rank, size, i, count = 0, total_count = 0;
    int a[N];
    
    // Inicializa o vetor com valores
    for (i = 0; i < N; i++) {
        a[i] = i;
    }


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divisão do trabalho
    int chunk_size = N / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? N : start + chunk_size;

    // Contagem local
    for (i = start; i < end; i++) {
        if (a[i] % 2 == 0) {
            count++;
        }
    }

    // Redução
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total de pares: %d\n", total_count);
    }

    MPI_Finalize();
    return 0;
}
