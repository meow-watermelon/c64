#include <c64.h>
#include <cbm.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* TODO: add device auto-detect feature */
#define DEVICE_NAME 8

#define TESTDATA_FILENAME "testdata"
#define TESTDATA_SIZE 16384

static unsigned char disk_buffer[TESTDATA_SIZE];

static void clear_screen(void) {
    __asm__("jsr $E544");
}

static void disk_benchmark(unsigned char device_name, unsigned char mode, unsigned char count) {
    unsigned char ret_open;
    int ret_read, ret_write;
    struct timespec start, end;

    /* clear memory */
    memset(disk_buffer, 0, TESTDATA_SIZE);

    if (mode == CBM_READ) {
        ret_open = cbm_open(1, device_name, CBM_READ, TESTDATA_FILENAME);
        if (ret_open != 0) {
            printf("ERROR: failed to open device %d: %d\n", device_name, ret_open);
            return;
        }

        /* start timer */
        clock_gettime(CLOCK_REALTIME, &start);

        /* read data */
        ret_read = cbm_read(1, disk_buffer, TESTDATA_SIZE);
        if (ret_read < 0) {
            printf("ERROR: failed to read data\n");
            cbm_close(1);
            return;
        }
        if (ret_read != TESTDATA_SIZE) {
            printf("ERROR: read %d byte(s) only\n", ret_read);
            cbm_close(1);
            return;
        }

        /* stop timer */
        clock_gettime(CLOCK_REALTIME, &end);

        /* close file */
        cbm_close(1);

        /* print period time */
        printf("[%d] DEV %d READ SPEED: %lu B/S\n", count, device_name, (unsigned long int)(TESTDATA_SIZE / (end.tv_sec - start.tv_sec)));
    }

    if (mode == CBM_WRITE) {
        /* delete writetest file first, ignore error on deleting file */
        cbm_open(15, device_name, 15, "s0:writetest");
        cbm_close(15);

        /* open new file for benchmark */
        ret_open = cbm_open(1, device_name, CBM_WRITE, "writetest");
        if (ret_open != 0) {
            printf("ERROR: failed to open device %d: %d\n", device_name, ret_open);
            return;
        }

        /* start timer */
        clock_gettime(CLOCK_REALTIME, &start);

        /* write data */
        ret_write = cbm_write(1, disk_buffer, TESTDATA_SIZE);
        if (ret_write < 0) {
            printf("ERROR: failed to write data\n");
            cbm_close(1);
            return;
        }
        if (ret_write != TESTDATA_SIZE) {
            printf("ERROR: write %d byte(s) only\n", ret_write);
            cbm_close(1);
            return;
        }

        /* stop timer */
        clock_gettime(CLOCK_REALTIME, &end);

        /* close file */
        cbm_close(1);

        /* print period time */
        printf("[%d] DEV %d WRITE SPEED: %lu B/S\n", count, device_name, (unsigned long int)(TESTDATA_SIZE / (end.tv_sec - start.tv_sec)));
    }
}

int main(void) {
    unsigned char round = 10;
    unsigned char i;

    /* clear screen */
    clear_screen();

    /* print memory address that is used for buffer */
    printf("BUFFER MEMORY ADDRESS: %p\n", disk_buffer);

    /* start benchmark procedure */
    for (i = 1; i <= round; ++i) {
        disk_benchmark(DEVICE_NAME, CBM_READ, i);
    }

    for (i = 1; i <= round; ++i) {
        disk_benchmark(DEVICE_NAME, CBM_WRITE, i);
    }

    return 0;
}
