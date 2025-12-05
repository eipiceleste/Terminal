#include <stdio.h>
#include "menu_dialogue.h"
#include "save.h"
#include "utils.h"

void dialogue_screen(GameState *gs) {
    printf("\n\nAqui comeca o dialogo (Sistema a ser Implementado com Arquivos de Acesso Binario)\n");
    printf("1 - Opcao de dialogo\n");
    printf("2 - Salvar e sair\n");
    printf("ESC - Sair\n");

    int opc = answer();

    switch (opc) {
        case 0:
            gs->mode = STATE_MENU;
            break;
        case 1:
            gs->mode = STATE_MINIGAME;
            break;
        case 2:
            if (save_game(gs, "data/save.dat")) {
                printf("Jogo salvo\n");
            }
            gs->mode = STATE_MENU;
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }
}