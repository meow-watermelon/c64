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

static void disk_benchmark(unsigned char device_name, unsigned char mode) {
    unsigned char ret_open;
    int ret_read;
    clock_t start;

    /* clear memory */
    memset(disk_buffer, 0, TESTDATA_SIZE);

    /* detect mode. TODO: add CBM_WRITE support */
    if (mode == CBM_READ) {
        ret_open = cbm_open(1, device_name, CBM_READ, TESTDATA_FILENAME);
        if (ret_open != 0) {
            printf("ERROR: failed to open device %d: %d\n", device_name, ret_open);
            return;
        }

        /* print memory address that is used for buffer */
        printf("ADDRESS: %p\n", disk_buffer);

        /* start timer */
        start = clock();

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

        /* print period time */
        printf("DEV %d READ SPEED: %u B/S\n", device_name, (unsigned int)(TESTDATA_SIZE / ((clock() - start) / CLOCKS_PER_SEC)));

        /* close file */
        cbm_close(1);
    }
}

int main(void) {
    unsigned char round = 10;
    unsigned char i;

    /* clear screen */
    clear_screen();

    /* start benchmark procedure */
    for (i = 1; i <= round; ++i) {
        printf("ROUND [%d]\n", i);
        disk_benchmark(DEVICE_NAME, CBM_READ);
    }

    return 0;
}
