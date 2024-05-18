#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define MAX_THREADS 8

typedef struct {
    double (*a)[N];
    double (*b)[N];
    double (*c)[N];
    int start;
    int end;
} ThreadData;

void* multiply_matrix(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int i, j, k;
    for (i = data->start; i < data->end; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                data->c[i][j] += data->a[i][k] * data->b[k][j];
            }
        }
    }
    pthread_exit(0);
}

int main(int argc, char** argv) {
    double a[N][N], b[N][N], c[N][N];
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    int i, j, num_threads;

    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            c[i][j] = 0.0;
        }
    }

    for (i = 0; i < num_threads; i++) {
        thread_data[i].a = a;
        thread_data[i].b = b;
        thread_data[i].c = c;
        thread_data[i].start = i * (N / num_threads);
        thread_data[i].end = (i + 1) * (N / num_threads);
        pthread_create(&threads[i], NULL, multiply_matrix, &thread_data[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
