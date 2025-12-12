#ifndef CARD_HISTORY_H
#define CARD_HISTORY_H

#include "deck.h"

#define CODE_LENGTH 4        // 4 cartas no código secreto
#define MAX_HISTORY 100      // Máximo de 100 jogadas no histórico

// Guarda uma tentativa do jogador (usado no minigame)
// O minigame chama history_add_play_record() pra cada palpite
typedef struct {
    Card guess[CODE_LENGTH];     // O que o jogador chutou
    int correct_pos;             // Cartas na posição certa
    int correct_value;           // Cartas com valor certo, posição errada
    int user_suit_wins;          // Quantos naipes o jogador ganhou
    int cpu_suit_wins;           // Quantos naipes a CPU ganhou
} PlayRecord;

// Histórico completo do minigame atual
// É salvo/recuperado pelo sistema de save
typedef struct {
    Card secret[CODE_LENGTH];      // Código secreto que tem que adivinhar
    int num_records;               // Quantas tentativas já fez
    PlayRecord records[MAX_HISTORY]; // Lista de todas tentativas
} CardHistory;

// Essas funções são declaradas mas não tão sendo usadas no código atual
// Elas existem pra permitir expansão de funcionalidades com o inventário ou debug de jogadas, ou facilitar a jogabilidade
void history_add_play_record(Card guess[4], int pos, int val, int user_suit, int cpu_suit);
void history_clear(void);          // Limpa histórico (nunca chamado)
void history_get(CardHistory *out); // Pega histórico (nunca chamado)
void history_set(const CardHistory *in); // Configura histórico (nunca chamado)
void history_set_secret(const Card secret[4]); // Seta código secreto (nunca chamado)
void history_get_secret(Card secret_out[4]); // Pega código secreto (nunca chamado)
void history_print(void);          // Mostra histórico na tela (nunca chamado)

#endif