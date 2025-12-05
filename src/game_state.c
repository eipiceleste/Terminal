#include <stdio.h>
#include "game_state.h"
#include "save.h"
#include "menu.h"
#include "menu_dialogue.h"
#include "menu_minigame.h"

void init_gamestate(GameState *gs) {
    gs->mode = STATE_MENU;
    gs->running = 1;
    gs->player.clues_found = 0;
    gs->player.inventory[0] = '\0';
    gs->player.name[0] = '\0';
}

void gameloop(GameState *gs) {
    while (gs->running) {
        switch (gs->mode) {
            case STATE_MENU:
                menu_screen(gs);
                break;
            case STATE_DIALOGUE:
                dialogue_screen(gs);
                break;
            case STATE_MINIGAME:
                minigame_screen(gs);
                break;
            case STATE_EXIT:
                gs->running = 0;
                break;
            default:
                gs->mode = STATE_MENU;
                break;
        }
    }
}

void debug_print(GameState *gs) {
    printf("GameState Debug Info:\n");
    printf("Mode: %d\n", gs->mode);
    printf("Player Name: %s\n", gs->player.name);
    printf("Clues Found: %d\n", gs->player.clues_found);
    printf("Inventory: %s\n", gs->player.inventory);
    printf("Running: %d\n", gs->running);
}