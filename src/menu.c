#include <stdio.h>
#include "menu.h"
#include "utils.h"
#include "save.h"

void menu_screen(GameState *gs) {
    printf("\n\nTERMINAL MENU PRINCIPAL\n");
    printf("1 - Novo Jogo\n");
    printf("2 - Carregar Jogo\n");
    printf("ESC - Sair do jogo\n");

    int opc = answer();

    switch (opc) {
        case 0:
            gs->mode = STATE_EXIT;
            break;
        case 1:
            init_gamestate(gs);
            clear_save_file();
            gs->mode = STATE_DIALOGUE;
            break;
        case 2:
            if (load_game(gs, "data/save.dat")) {
                printf("Save carregado.\n");
                debug_print(gs);
                gs->mode = STATE_DIALOGUE;
            } else {
                printf("Nenhum save encontrado.\n");
            }
            break;
        default:
            printf("Opcao Invalida\n");
            break;
    }
}