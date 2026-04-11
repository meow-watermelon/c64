#include <c64.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* C64 memory addresses for screen position + color */
#define SCREEN_BASE ((unsigned char*)0x0400)
#define COLOR_BASE  ((unsigned char*)0xD800)

static void sleep_second(unsigned short int second) {
    clock_t start = clock();

    while ((clock() - start) / CLOCKS_PER_SEC < second) {
        /* do nothing */
    }
}

static void find_prime(unsigned long int min, unsigned long int max) {
    unsigned long int prime = min;
    unsigned long int divisor;
    unsigned long int count = 0;

    clock_t start;
    clock_t end;

    start = clock();

    for(;;) {
        if (prime >= max) {
            break;
        }

        for (divisor = 1; divisor <= prime / 2; ++divisor) {
            if (prime % divisor == 0) {
                ++count;
            }
        }

        if (count == 1) {
            end = clock();
            printf("PRIME NUMBER: %lu TIME: %lu\n", prime, (unsigned long int)(end - start) / CLOCKS_PER_SEC);
        }

        count = 0;
        ++prime;
    }
}

static void color_wash(unsigned int count) {
    unsigned int i = 0;
    unsigned char color = 0;
    VIC.addr = 0x14;

    while (count > 0) {
        /* shapes */
        for (i = 0; i < 1000; ++i) {
            SCREEN_BASE[i] = 64 + (rand() % 64);
            COLOR_BASE[i] = (rand() % 16);
        }

        /* chars */
        for (i = 0; i < 1000; ++i) {
            SCREEN_BASE[i] = 0 + (rand() % 64);
            COLOR_BASE[i] = (rand() % 16);
        }

        --count;
    }

    VIC.addr = 0x17;
}

int main(void) {
    while (kbhit() == 0) {
        clrscr();
        /* TEST 1: find prime numbers */
        find_prime(2, 100);

        clrscr();
        /* TEST 2: color wash */
        color_wash(10);
    }

    /* reset */
    VIC.addr = 0x14;
    textcolor(COLOR_LIGHTBLUE);
    clrscr();

    return 0;
}
