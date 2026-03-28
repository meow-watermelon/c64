/*
 * compilation: cl65 -O -t c64 -o find-prime-number.prg find-prime-number.c
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_NUMBER 2
#define MAX_NUMBER UINTMAX_MAX

unsigned long int min_num = MIN_NUMBER;

int main() {
    unsigned long int prime = min_num;
    unsigned long int divisor;
    unsigned long int count = 0;
    clock_t start;
    clock_t end;

    start = clock();

    for(;;) {
        if (prime >= MAX_NUMBER) {
            break;
        }

        for (divisor = 1; divisor <= prime / 2; ++divisor) {
            if (prime % divisor == 0) {
                ++count;
            }
        }

        if (count == 1) {
            end = clock();
            printf("prime number: %lu time: %lu\n", prime, (unsigned long int)(end - start) / CLOCKS_PER_SEC);
        }

        count = 0;
        ++prime;
    }

    exit(EXIT_SUCCESS);
}
