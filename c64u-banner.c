#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define C64U_BANNER "C= Commodore 64 Ultimate C="

static unsigned char pick_color(unsigned char color_max) {
    return rand() % color_max;
}

static unsigned char pick_position(char min, char max) {
    return (rand() % (max - min + 1)) + min;
}

static void sleep_second(unsigned short int second) {
    clock_t start = clock();

    while ((clock() - start) / CLOCKS_PER_SEC < second) {
        /* do nothing */
    }
}

int main() {
    /* postion variables */
    unsigned char x, y;
    unsigned char x_range_min, x_range_max, y_range_min, y_range_max;

    /* text color variables */
    unsigned char text_colors[] = {
        COLOR_BLACK,
        COLOR_WHITE,
        COLOR_RED,
        COLOR_CYAN,
        COLOR_VIOLET,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_YELLOW,
        COLOR_ORANGE,
        COLOR_BROWN,
        COLOR_LIGHTRED,
        COLOR_GRAY1,
        COLOR_GRAY2,
        COLOR_LIGHTGREEN,
        COLOR_LIGHTBLUE,
        COLOR_GRAY3
    };
    size_t color_number = sizeof(text_colors) / sizeof(text_colors[0]);

    /* get original text color */
    unsigned char origin_text_color = textcolor(COLOR_WHITE);

    unsigned char banner_length;
    banner_length = (unsigned char)strlen(C64U_BANNER);

    /* get screen size */
    screensize(&x, &y);

    /* calculate banner movement range */
    x_range_min = 0;
    x_range_max = x - banner_length;
    y_range_min = 0;
    y_range_max = y - 1;

    /* use kbhit() to check if key is pressed */
    while (kbhit() == 0) {
        /* clear screen */
        clrscr();

        /* show banner in random place within available (x, y) range */
        textcolor(text_colors[pick_color(color_number)]);
        cputsxy(pick_position(x_range_min, x_range_max), pick_position(y_range_min, y_range_max), C64U_BANNER);

        /* sleep 1 second */
        sleep_second(1);
    }

    /* set original text color */
    textcolor(origin_text_color);

    /* exit if any key is pressed */
    cgetc();
    clrscr();

    return 0;
}

