#include <c64.h>
#include <cbm.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DISK_DATA ((unsigned char*)0xA000)
#define KOALA_FILE_SIZE 10003
#define FILE_INDEX 12

static void sleep_second(unsigned short int second) {
    clock_t start = clock();

    while ((clock() - start) / CLOCKS_PER_SEC < second) {
        /* do nothing */
    }
}

static void show_picture(unsigned char *filename) {
    memset(DISK_DATA, 0, KOALA_FILE_SIZE);

    if (cbm_open(1, 8, CBM_READ, filename) == 0) {
        cbm_read(1, DISK_DATA, KOALA_FILE_SIZE);
        cbm_close(1);

        /* bitmap */
        memcpy((void*)0x4000, &DISK_DATA[2], 8000);

        /* screen */
        memcpy((void*)0x6000, &DISK_DATA[8002], 1000);

        /* color */
        memcpy((void*)0xD800, &DISK_DATA[9002], 1000);

        VIC.bgcolor0 = DISK_DATA[10002];
        VIC.bordercolor = 0;
    } else {
        /* red if wrong */
        VIC.bordercolor = 2;
    }
}

int main(void) {
    unsigned char fname[10];
    unsigned int i = 1;

    CIA2.pra &= 0xFC;
    CIA2.pra |= 0x02;

    VIC.addr = 0x80;

    VIC.ctrl1 |= 0x20; 
    VIC.ctrl2 |= 0x10;


    /* Wait for a keypress before ending */
    while(kbhit() == 0) {
        for (i = 1; i <= FILE_INDEX; ++i) {
            sprintf(fname, "s%d.bin", i);
            show_picture(fname);
            sleep_second(20);
        }
    }

    /* reset */
    VIC.ctrl1 &= ~0x20;
    CIA2.pra = (CIA2.pra & 0xFC) | 0x03;

    return 0;
}
