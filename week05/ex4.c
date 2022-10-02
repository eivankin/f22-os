#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define run_with_mutex(instruction, mutex) \
if (pthread_mutex_lock(&mutex) != 0) \
    print_error_and_die("pthread_mutex_lock"); \
instruction; \
if (pthread_mutex_unlock(&mutex) != 0) \
    print_error_and_die("pthread_mutex_unlock")

void print_error_and_die(const char *func_name) {
    perror(func_name);
    exit(EXIT_FAILURE);
}

void init_mutex(pthread_mutex_t *mutex) {
    if (pthread_mutex_init(mutex, NULL) != 0)
        print_error_and_die("pthread_mutex_init");
}

int is_prime(int n) {
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int n = 0;

pthread_mutex_t get_number_lock = PTHREAD_MUTEX_INITIALIZER,
        increment_primes_count_lock = PTHREAD_MUTEX_INITIALIZER;

int next_number_to_check = 0;
int primes_found_so_far = 0;

int get_number_to_check() {
    int ret = next_number_to_check;
    if (next_number_to_check != n)
        next_number_to_check++;
    return ret;
}

void increment_primes() {
    primes_found_so_far++;
}

void *check_primes(void *arg) {
    while (next_number_to_check < n) {
        run_with_mutex(int num = get_number_to_check(), get_number_lock);

        if (is_prime(num)) {
            // prevent multiple threads to increment the number of primes at the same time
            run_with_mutex(increment_primes(), increment_primes_count_lock);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    int n_threads = atoi(argv[2]);
    n = atoi(argv[1]);

    init_mutex(&get_number_lock);
    init_mutex(&increment_primes_count_lock);

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
    for (int i = 0; i < n_threads; i++) {
        if (pthread_create(&threads[i], NULL,
                           check_primes, NULL) != 0)
            print_error_and_die("pthread_create");
    }
    for (int i = 0; i < n_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0)
            print_error_and_die("pthread_join");
    }

    free(threads);

    printf("%d\n", primes_found_so_far);
    exit(EXIT_SUCCESS);
}
