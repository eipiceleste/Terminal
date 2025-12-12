#include <stdio.h>
#include <stdlib.h>
#include "game_state.h"
#include "save.h"

// Ponto de entrada do programa
int main(void) {
    GameState gs;
    init_gamestate(&gs);  // Inicializa estado
    
    gameloop(&gs);  // Entra no loop principal
    
    free_gamestate(&gs);  // Limpa memória antes de sair
    printf("\nJogo encerrado.\n");
    return 0;
}