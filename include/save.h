#ifndef SAVE_H
#define SAVE_H

#include "game_state.h"

int save_game(GameState *gs, const char *savefile);
int load_game(GameState *gs, const char *savefile);

#endif