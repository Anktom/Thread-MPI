#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 8

typedef struct {
    int *a;
    int start;
    int end;
    int count;
} ThreadData;

void* count_even(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int count = 0;
    for (int i = data->start; i < data->end; i++) {
        if (data->a[i] % 2 == 0) {
            count++;
        }
    }
    data->count = count;
    pthread_exit(0);
}

int main(int argc, char** argv) {
    int n = 1000;
    int a[n];
    int total_count = 0;
    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    int i, num_threads;

    for (num_threads = 1; num_threads <= MAX_THREADS; num_threads++) {
        total_count = 0;

        for (i = 0; i < n; i++) {
            a[i] = rand() % 100; 
        }
        for (i = 0; i < num_threads; i++) {
            thread_data[i].a = a;
            thread_data[i].start = i * (n / num_threads);
            thread_data[i].end = (i + 1) * (n / num_threads);
            pthread_create(&threads[i], NULL, count_even, &thread_data[i]);
        }

        for (i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
            total_count += thread_data[i].count;
        }

        printf("Total de números pares com %d threads: %d\n", num_threads, total_count);
    }

    return 0;
}
