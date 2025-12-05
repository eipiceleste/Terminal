#include "game_state.h"
#include "save.h"

int main(void) {
    GameState gs;
    gameloop(&gs);
    return 0;
}