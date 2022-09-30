#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int primes_count_in_interval(int start, int finish)
{
    int ret = 0;
    for (int i = start; i < finish; i++)
        if (is_prime(i) != 0)
            ret++;
    return ret;
}

// The structure that will be passed to the threads, corresponding to an interval to count the number of primes in.
typedef struct prime_counter_request
{
    int start, finish;
} prime_counter_request;

void *prime_counter(void *arg)
{
    prime_counter_request *request = (prime_counter_request *) arg;
    int *result = malloc(sizeof(int));
    *result = primes_count_in_interval(request->start, request->finish);
    pthread_exit(result);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Not enough arguments\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]), n_threads = atoi(argv[2]);
    int segment_size = n / n_threads + (n % n_threads == 0 ? 0 : 1);

    pthread_t threads[n_threads];
    prime_counter_request requests[n_threads];

    for (int i = 0; i < n_threads; i++)
    {
        requests[i].start = i * segment_size;
        requests[i].finish = fmin((i + 1) * segment_size, n);
        int status = pthread_create(&threads[i], NULL,
                                    prime_counter, (void *) &requests[i]);
        if (status != 0) {
            printf("Failed to create a new thread: %s\n", strerror(status));
        }
    }

    int total_result = 0;
    for (int i = 0; i < n_threads; i++)
    {
        int *threadResult;
        int status = pthread_join(threads[i], (void **) &threadResult);
        if (status != 0) {
            printf("Failed to fetch results: %s\n", strerror(status));
            return EXIT_FAILURE;
        }
        total_result += *threadResult;
    }

    printf("%d\n", total_result);

    return EXIT_SUCCESS;
}
