#ifndef DECK_H
#define DECK_H

#include <stddef.h>

#define NUM_CARDS 16        // 4 valores × 4 naipes = 16 cartas
#define CODE_LENGTH 4       // Código tem 4 cartas
#define MAX_ATTEMPTS 8      // Pode tentar no máximo 8 vezes
#define NAME_LENGTH 20      // Tamanho máximo do nome do jogador (funcionando separadamente do nome do game_state atualmente)

// Representa uma carta individual
typedef struct {
    char value;    // 'A','J','Q','K'
    char suit;     // 'H'(♥),'C'(♣),'D'(♦),'S'(♠)
    int revealed;  // 1 se já foi revelada/acertada (usado no minigame)
} Card;

// Nó de lista ligada (o baralho é uma lista de cartas)
typedef struct CardNode {
    Card card;              // A carta em si
    int index;              // Posição original (0-15)
    struct CardNode *next;  // Próxima carta
} CardNode;

// Baralho completo (lista ligada de cartas)
typedef struct {
    CardNode *head;  // Primeira carta
    int size;        // Quantas cartas tem
} Deck;

// Cria baralho vazio (só aloca memória)
Deck* deck_create(void);

// Destrói baralho e todas cartas (libera memória)
void deck_destroy(Deck *d);

// Cria um nó com uma carta (aloca memória)
CardNode* deck_create_node(Card c, int idx);

// Adiciona carta no final do baralho
void deck_add_node(Deck *d, CardNode *node);

// Cria baralho completo com 16 cartas (A-K × ♥♣♦♠)
void deck_init_full(Deck *d);

// Pega carta na posição X (0 = primeira carta)
// Usado no minigame pra pegar carta escolhida
CardNode* deck_get_node_at(Deck *d, int index);

// Retorna quantas cartas tem no baralho
int deck_size(const Deck *d);

// Mostra todas cartas numeradas (1: A♥  2: A♣ ...)
void deck_display(Deck *d);

#endif