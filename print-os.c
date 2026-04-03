/*
 * compilation: cl65 -O -t c64 -o print-os.prg print-os.c
 */

#include <c64.h>
#include <stdio.h>

int main() {
    unsigned int os_type;
    unsigned char *os_type_string;

    os_type = get_ostype();

    switch (os_type) {
        case 0xAA:
            os_type_string = "C64 US";
            break;
        case 0x64:
            os_type_string = "PET 64";
            break;
        case 0x43:
            os_type_string = "SX-64";
            break;
        case 0x03:
            os_type_string = "C64 EU NEW";
            break;
        case 0x00:
            os_type_string = "C64 EU OLD";
            break;
        case 0xFF:
            os_type_string = "C64 DTV";
            break;
        default:
            os_type_string = "N/A";
            break;
    }

    printf("OS TYPE: %s\n", os_type_string);

    return 0;
}
