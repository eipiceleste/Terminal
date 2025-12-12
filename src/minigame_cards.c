#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "minigame_cards.h"
#include "save.h"
#include "deck.h"
#include "card_utils.h"

// Pega índices das cartas do deck (pra salvar)
void deck_to_indices(Deck *d, int indices[]) {
    if (!d) return;
    
    CardNode *cur = d->head;
    int i = 0;
    while (cur && i < NUM_CARDS) {
        indices[i] = cur->index;
        cur = cur->next;
        i++;
    }
}

// Gera código secreto de 4 cartas aleatórias
void generate_secret_code(Deck *d, Card secret[]) {
    if (!d || d->size == 0) return;
    
    int used[NUM_CARDS] = {0};
    for (int i = 0; i < CODE_LENGTH; i++) {
        int index;
        do {
            index = rand() % d->size;  // Cartas diferentes
        } while (used[index]);
        
        used[index] = 1;
        CardNode *node = deck_get_node_at(d, index);
        if (node) {
            secret[i] = node->card;
            secret[i].revealed = 0;  // Começa não revelada
        }
    }
}

// Verifica se escolha do jogador é válida
int validate_choice(Deck *d, int choices[], Card guess[]) {
    if (!d) return 0;
    
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (choices[i] < 1 || choices[i] > d->size) return 0;
        
        // Não pode repetir carta
        for (int j = 0; j < i; j++) {
            if (choices[i] == choices[j]) return 0;
        }
        
        CardNode *node = deck_get_node_at(d, choices[i] - 1);
        if (!node) return 0;
        guess[i] = node->card;
    }
    return 1;
}

// Prepara minigame novo
void minigame_init(GameState *gs) {
    srand((unsigned)time(NULL));
    
    if (!gs->minigame_deck) {
        gs->minigame_deck = deck_create();
        deck_init_full(gs->minigame_deck);
    }
    
    // Gera código secreto
    generate_secret_code(gs->minigame_deck, gs->minigame_save.secret);
    
    // Guarda estado do deck (pra poder recriar depois)
    deck_to_indices(gs->minigame_deck, gs->minigame_save.deck_indices);
    gs->minigame_save.deck_size = deck_size(gs->minigame_deck);
    
    // Zera contadores
    gs->minigame_save.attempts = 0;
    gs->minigame_save.score = 0;
    gs->minigame_save.completed = 0;
}

// Joga uma rodada (uma tentativa)
void minigame_play_round(GameState *gs) {
    if (!gs->minigame_deck) return;
    
    printf("\n--- Tentativa %d/%d ---\n", 
           gs->minigame_save.attempts + 1, MAX_ATTEMPTS);
    
    // Mostra código (cartas reveladas aparecem, outras são [?])
    printf("[CODIGO] ");
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (gs->minigame_save.secret[i].revealed) {
            printf("%c%c ", gs->minigame_save.secret[i].value, 
                   gs->minigame_save.secret[i].suit);
        } else {
            printf("[?] ");
        }
    }
    printf("\n");
    
    // Mostra baralho disponível
    deck_display(gs->minigame_deck);
    
    // Pede 4 cartas
    int choices[CODE_LENGTH];
    Card guess[CODE_LENGTH];
    
    printf("Escolha %d cartas (1-%d): ", CODE_LENGTH, deck_size(gs->minigame_deck));
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (scanf("%d", &choices[i]) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            return;
        }
    }
    while (getchar() != '\n');  // Limpa buffer
    
    if (!validate_choice(gs->minigame_deck, choices, guess)) {
        printf("Escolha invalida! Use 4 cartas diferentes.\n");
        return;
    }
    
    // Analisa o palpite
    int correct_pos, correct_val, player_wins, computer_wins;
    analyze_guess(gs->minigame_save.secret, guess, &correct_pos, &correct_val,
                  &player_wins, &computer_wins);
    
    // Mostra o que escolheu
    printf("\nPalpite: ");
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf("%c%c ", guess[i].value, guess[i].suit);
    }
    printf("\n");
    
    // Mostra resultado
    printf("\n=== FEEDBACK ===\n");
    printf("Posicoes corretas: %d\n", correct_pos);
    printf("Valores corretos: %d\n", correct_val);
    printf("Naipes: Voce %d - PC %d\n", player_wins, computer_wins);
    
    // Atualiza estado
    gs->minigame_save.attempts++;
    gs->minigame_save.score += correct_pos * 10 + player_wins * 5;
}

// Mostra código secreto (quando perde)
void display_minigame_result(GameState *gs) {
    printf("\nCodigo: ");
    for (int i = 0; i < CODE_LENGTH; i++) {
        printf("%c%c ", gs->minigame_save.secret[i].value, 
               gs->minigame_save.secret[i].suit);
    }
    printf("\n");
}

// Função principal do minigame - controla o jogo inteiro
void iniciar_minigame_cartas(GameState *gs) {
    // Recria baralho se necessário
    if (!gs->minigame_deck || gs->minigame_save.deck_size == 0) {
        rebuild_deck_from_save(gs);
        minigame_init(gs);
    }
    
    printf("\n=== DESAFIO DE DESCRIPTOGRAFIA ===\n");
    printf("Voce encontrou um arquivo criptografado.\n");
    printf("Decifre o codigo para acessar seu conteudo.\n\n");
    
    // Loop principal: até 8 tentativas ou acertar
    while (gs->minigame_save.attempts < MAX_ATTEMPTS && 
           !gs->minigame_save.completed) {
        minigame_play_round(gs);
        
        // Verifica se ganhou (todas cartas reveladas)
        gs->minigame_save.completed = 1;
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (!gs->minigame_save.secret[i].revealed) {
                gs->minigame_save.completed = 0;
                break;
            }
        }
        
        if (gs->minigame_save.completed) {
            printf("\n*** DESCRIPTOGRAFADO! ***\n");
            printf("Voce decifrou o arquivo em %d tentativas!\n", 
                   gs->minigame_save.attempts);
            
            // Recompensa
            gs->player.clues_found++;
            printf("\n[+] Nova pista adicionada ao inventario!\n");
            printf("[+] Total de pistas: %d\n", gs->player.clues_found);

            gs->minigame_save.completed = 1;
            
            // Salva automaticamente
            if (game_save(gs, "data/save.dat")) {
                printf("[+] Progresso salvo.\n");
            }
            return;
        }
        
        printf("\nPressione Enter para continuar...");
        while (getchar() != '\n');
    }
    
    // Se chegou aqui, perdeu
    printf("\n*** FALHA NA DESCRIPTOGRAFIA ***\n");
    printf("Tentativas esgotadas.\n");
    display_minigame_result(gs);
}