#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "utils.h"


// Text Utils
int answer() {
    char c = _getch();
    if (c == 27) return 0;
    int opc = c - '0';
    printf("\n\n");
    Sleep(200);
    return opc;
}

// System Utils
void clear_save_file(void) {
    FILE *f = fopen("data/save.dat", "w");
    if (f != NULL) {
        fclose(f);
    }
}