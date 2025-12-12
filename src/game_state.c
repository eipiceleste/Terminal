#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_state.h"
#include "save.h"
#include "menu.h"
#include "menu_dialogue.h"
#include "menu_minigame.h"
#include "deck.h"
#include "dialogue.h"

// Prepara estado novo do jogo
void init_gamestate(GameState *gs) {
    gs->mode = STATE_MENU;
    gs->player.clues_found = 0;
    gs->player.inventory[0] = '\0';
    strcpy(gs->player.name, "Alice");  // Nome padrão
    
    // Zera dados do minigame
    memset(&gs->minigame_save, 0, sizeof(MiniGameSave));
    
    // Deck começa vazio
    gs->minigame_deck = NULL;
}

// Libera tudo que foi alocado
void free_gamestate(GameState *gs) {
    if (gs->minigame_deck) {
        deck_destroy(gs->minigame_deck);
    }
    dialogue_free(); // Diálogos também usam memória
}

// Loop principal chama tela certa baseado no estado
void gameloop(GameState *gs) {
    while (gs->mode != STATE_EXIT) {
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
            default:
                gs->mode = STATE_MENU;
                break;
        }
    }
}

// Mostra estado atual pra debug
void debug_print(GameState *gs) {
    printf("\n=== DEBUG ===\n");
    printf("Modo: %d\n", gs->mode);
    printf("Nome: %s\n", gs->player.name);
    printf("Pistas: %d\n", gs->player.clues_found);
    printf("Minigame: %s\n", gs->minigame_save.completed ? "Completo" : "Incompleto");
    printf("Tentativas: %d/%d\n", gs->minigame_save.attempts, MAX_ATTEMPTS);
    printf("Deck size: %d\n", gs->minigame_save.deck_size);
}

// Recria baralho quando carrega save
void rebuild_deck_from_save(GameState *gs) {
    if (!gs) return;
    
    // Apaga deck antigo se existir
    if (gs->minigame_deck) {
        deck_destroy(gs->minigame_deck);
    }
    
    // Cria novo deck com todas cartas
    gs->minigame_deck = deck_create();
    if (gs->minigame_deck) {
        deck_init_full(gs->minigame_deck);
    }
}