#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <stdio.h>
#include <time.h>  // Para medir o tempo

#define N 1000  // Tamanho do vetor
#define NUM_THREADS 4  // Número de threads

int a[N];
int count = 0;
pthread_mutex_t count_mutex;

void *count_even(void *arg) {
    int id = *(int *)arg;
    int chunk_size = N / NUM_THREADS;
    int start = id * chunk_size;
    int end = (id == NUM_THREADS - 1) ? N : start + chunk_size;
    int local_count = 0;

    for (int i = start; i < end; i++) {
        if (a[i] % 2 == 0) {
            local_count++;
        }
    }

    pthread_mutex_lock(&count_mutex);
    count += local_count;
    pthread_mutex_unlock(&count_mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Inicializa o vetor com valores
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    pthread_mutex_init(&count_mutex, NULL);

    // Medindo o tempo de execução
    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, count_even, (void *)&thread_ids[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Total de pares: %d\n", count);
    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    pthread_mutex_destroy(&count_mutex);
    return 0;
}
