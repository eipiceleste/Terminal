#include <stdio.h>
#include "save.h"

int save_game(GameState *gs, const char *savefile) {
    FILE *f = fopen(savefile, "wb");
    if (!f) return 0;

    fwrite(gs, sizeof(GameState), 1, f);
    fclose(f);
    return 1;
}

int load_game(GameState *gs, const char *savefile) {
    FILE *f = fopen(savefile, "rb");
    if (!f) return 0;

    fread(gs, sizeof(GameState), 1, f);
    fclose(f);
    return 1;
}