#include <stdio.h>
#include <stdlib.h>

/**
 * Test results:
 * 10
 * Hits: 10, misses: 990, hit/miss ratio: 0.010101
 *
 * 50
 * Hits: 51, misses: 949, hit/miss ratio: 0.053741
 *
 * 100
 * Hits: 93, misses: 907, hit/miss ratio: 0.102536
 */

#define INPUT_PATH "input.txt"
#define counter_t unsigned char
#define DEFAULT_ID 0

// set to 1 to print counter values and ids of cached pages
#define DEBUG 0

const unsigned COUNTER_LEN = sizeof(counter_t) * 8; // counter length in bits


void print_binary(counter_t number, int depth)
{
    if (depth < COUNTER_LEN) {
        print_binary(number >> 1, depth + 1);
    }
    fputc((number & 1) ? '1' : '0', stdout);
}

typedef struct {
    unsigned id;
    counter_t r_bits;
} Page;

int main(int argc, char** argv) {
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL) {
        printf("Failed to open the input file '%s'", INPUT_PATH);
        return EXIT_FAILURE;
    }

    if (argc < 2) {
        printf("Number of page frames is not given");
        return EXIT_FAILURE;
    }

    int number_of_page_frames;
    if (sscanf(argv[1], "%d", &number_of_page_frames) < 1) {
        printf("Failed to parse the number of page frames");
        return EXIT_FAILURE;
    }

    if (number_of_page_frames <= 0) {
        printf("Number of page frames should be greater than zero");
        return EXIT_FAILURE;
    }

    Page pages[number_of_page_frames];
    for (int i = 0; i < number_of_page_frames; ++i) {
        pages[i] = (Page) {DEFAULT_ID, 0};
    }

    unsigned page_id, hits = 0, misses = 0;
    while (fscanf(input, "%u", &page_id) > 0) {
        int was_found = 0, updated_idx = 0;
        for (int i = 0; i < number_of_page_frames; ++i) {
            if (page_id == pages[i].id) {
                ++hits;
                was_found = 1;
                pages[i].r_bits = 1 << (COUNTER_LEN - 1) | pages[i].r_bits >> 1;
                updated_idx = i;
            }
        }

        if (!was_found) {
            ++misses;

            int min_index = -1;
            counter_t min_val;
            for (int i = 0; i < number_of_page_frames; ++i) {
                if (pages[i].id == DEFAULT_ID) {
                    min_index = i;
                    break;
                }

                if (min_index == -1 || (pages[i].r_bits < min_val)) {
                    min_index = i;
                    min_val = pages[i].r_bits;
                }
            }

            pages[min_index] = (Page) {page_id, 1 << (COUNTER_LEN - 1)};
            updated_idx = min_index;
        }

        for (int i = 0; i < number_of_page_frames; ++i) {
            if (i != updated_idx) {
                pages[i].r_bits = pages[i].r_bits >> 1;
            }
        }

        if (DEBUG) {
            printf("#%u %d\n", hits + misses, was_found);
            for (int i = 0; i < number_of_page_frames; ++i) {
                printf("%u\t", pages[i].id);
                print_binary(pages[i].r_bits, 1);
                printf("\n");
            }
        }
    }

    printf("Hits: %u, misses: %u, hit/miss ratio: %f\n", hits, misses, (double) hits / misses);

    return EXIT_SUCCESS;
}
