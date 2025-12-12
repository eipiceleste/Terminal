#include <stdio.h>
#include "menu_minigame.h"
#include "utils.h"
#include "save.h"
#include "minigame_cards.h"
#include "card_ui.h"

// Menu do minigame (antes de começar a jogar)
void minigame_screen(GameState *gs) {
    printf("\n=== DESCRIPTOGRAFAR ARQUIVO ===\n");
    printf("1 - Iniciar descriptografia\n");
    printf("2 - Ver regras\n");
    printf("3 - Teste rapido (debug)\n");  // Debug: mostra baralho
    printf("4 - Voltar ao dialogo\n");
    printf("ESC - Menu principal\n");
    
    int opc = answer();
    
    switch (opc) {
        case 0:
            gs->mode = STATE_MENU;
            break;
        case 1:
            iniciar_minigame_cartas(gs);  // Chama o minigame
            break;
        case 2:
            display_rules_simple();  // Mostra regras
            printf("\nPressione Enter para voltar...");
            while (getchar() != '\n');
            break;
        case 3:  // Debug: verifica se baralho tá funcionando
            printf("\n=== TESTE DEBUG ===\n");
            if (!gs->minigame_deck) {
                printf("Criando novo deck...\n");
                rebuild_deck_from_save(gs);
            }
            
            if (gs->minigame_deck) {
                printf("Deck existe! Tamanho: %d\n", deck_size(gs->minigame_deck));
                deck_display(gs->minigame_deck);  // Mostra cartas
            } else {
                printf("ERRO: Deck nao foi criado!\n");
            }
            
            printf("\nPressione Enter para voltar...");
            while (getchar() != '\n');
            break;
        case 4:
            gs->mode = STATE_DIALOGUE;
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }
}