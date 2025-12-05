#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    STATE_MENU,
    STATE_DIALOGUE,
    STATE_MINIGAME,
    STATE_INVENTORY,
    STATE_EXIT
} GameMode;

typedef struct {
    int clues_found;
    char inventory[100];
    char name[50];
} Player;

typedef struct {
    GameMode mode;
    Player player;
    int running;
} GameState;

void init_gamestate(GameState *gs);
void gameloop(GameState *gs);
void debug_print(GameState *gs);

#endif