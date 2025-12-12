#include "card_history.h"
#include <stdio.h>
#include <string.h>

// Histórico global (só existe um por jogo)
static CardHistory history;

// Adiciona uma jogada ao histórico
void history_add_play_record(Card guess[4], int pos, int val, int user_suit, int cpu_suit) {
    if (history.num_records >= MAX_HISTORY) return;
    
    PlayRecord *rec = &history.records[history.num_records++];
    memcpy(rec->guess, guess, sizeof(Card) * CODE_LENGTH);
    rec->correct_pos = pos;
    rec->correct_value = val;
    rec->user_suit_wins = user_suit;
    rec->cpu_suit_wins = cpu_suit;
}

// Limpa histórico (novo jogo)
void history_clear(void) {
    history.num_records = 0;
}

// Pega cópia do histórico
void history_get(CardHistory *out) {
    if (out) *out = history;
}

// Configura histórico (quando carrega save)
void history_set(const CardHistory *in) {
    if (in) history = *in;
}

// Define código secreto
void history_set_secret(const Card secret[4]) {
    memcpy(history.secret, secret, sizeof(Card) * CODE_LENGTH);
}

// Pega código secreto
void history_get_secret(Card secret_out[4]) {
    memcpy(secret_out, history.secret, sizeof(Card) * CODE_LENGTH);
}

// Mostra histórico na tela
void history_print(void) {
    printf("\n=== HISTORICO ===\n");
    for (int i = 0; i < history.num_records; i++) {
        PlayRecord *rec = &history.records[i];
        printf("Jogada %d: ", i + 1);
        for (int j = 0; j < CODE_LENGTH; j++) {
            printf("%c%c ", rec->guess[j].value, rec->guess[j].suit);
        }
        printf("| Pos=%d Val=%d | Naipe Voce=%d PC=%d\n",
               rec->correct_pos, rec->correct_value,
               rec->user_suit_wins, rec->cpu_suit_wins);
    }
}