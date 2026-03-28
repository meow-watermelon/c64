/*
 * cc65 compilation command
 * $ cl65 -O -t c64 -o power2orig.prg power2orig.c
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* initial number */
#define INITIAL_NUMBER 1000

/* initialized initial number */
unsigned long int init_num = INITIAL_NUMBER;

/*
 * a function to calculate power function in integer type
*/
static unsigned long int powi(unsigned long int base, unsigned short int exponent) {
    unsigned long int result = base;

    while (--exponent) {
        result *= base;
    }

    return result;
}

/*
 * a function to return length of an integer
*/
static unsigned short int integer_length(unsigned long int integer) {
    unsigned short int counter = 1;
    unsigned long int multiplier = 1;

    while (1) {
        if (integer / multiplier < 10) {
            break;
        }

        ++counter;
        multiplier *= 10;
    }

    return counter;
}

int main() {
    /* initialize variables */
    unsigned long int partial_multiplier = powi(10, integer_length(init_num) / 2);
    unsigned long int first = init_num / partial_multiplier;
    unsigned long int post = init_num % partial_multiplier;

    clock_t start;
    clock_t end;

    /* print maximum value of unsigned long int type */
    printf("Maximum value of unsigned long int type: %lu\n", UINTMAX_MAX);

    /* start timer */
    start = clock();

    for (;;) {

        /* exit loop once initial number is equal to or greater than UINTMAX_MAX */
        if (init_num >= UINTMAX_MAX) {
            printf("Hits maximum value of unsigned long int type: %lu\n", UINTMAX_MAX);
            exit(EXIT_SUCCESS);
        }

        /* show some progress */
        if (init_num % 100 == 0) {
            end = clock();
            printf("Passing %lu after %lu second(s)...\n", init_num, (end - start) / CLOCKS_PER_SEC);
        }

        if (integer_length(init_num) % 2 != 0) {
            init_num *= 10;
        }

        partial_multiplier = powi(10, integer_length(init_num) / 2);
        first = init_num / partial_multiplier;
        post = init_num % partial_multiplier;

        if ((first + post) * (first + post) == init_num) {
            if (integer_length(first) == integer_length(post)) {
                end = clock();

                /* write to the standard output */
                printf("first: %lu post: %lu found: %lu time: %lu\n", first, post, init_num, (unsigned long int)(end - start) / CLOCKS_PER_SEC);
            }
        }

        ++init_num;
    }

    return 0;
}
