#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

// Cria deck vazio
Deck* deck_create(void) {
    Deck *d = (Deck*)malloc(sizeof(Deck));
    if (!d) return NULL;
    
    d->head = NULL;
    d->size = 0;
    return d;
}

// Apaga deck e todas as cartas
void deck_destroy(Deck *d) {
    if (!d) return;
    
    CardNode *cur = d->head;
    while (cur) {
        CardNode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    
    free(d);
}

// Cria nó com uma carta
CardNode* deck_create_node(Card c, int idx) {
    CardNode *node = (CardNode*)malloc(sizeof(CardNode));
    if (!node) return NULL;
    
    node->card = c;
    node->index = idx;
    node->next = NULL;
    return node;
}

// Adiciona carta no final do deck
void deck_add_node(Deck *d, CardNode *node) {
    if (!d || !node) return;
    
    if (!d->head) {
        d->head = node;
    } else {
        CardNode *cur = d->head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    d->size++;
}

// Cria deck completo: 4 valores × 4 naipes = 16 cartas
void deck_init_full(Deck *d) {
    if (!d) return;
    
    char values[] = {'A','J','Q','K'};
    char suits[] = {'H','C','D','S'};
    
    int idx = 0;
    for (int s = 0; s < 4; s++) {
        for (int v = 0; v < 4; v++) {
            Card c;
            c.value = values[v];
            c.suit = suits[s];
            c.revealed = 0;
            
            CardNode *node = deck_create_node(c, idx++);
            if (node) {
                deck_add_node(d, node);
            }
        }
    }
}

// Pega carta na posição X (0 = primeira)
CardNode* deck_get_node_at(Deck *d, int index) {
    if (!d || index < 0 || index >= d->size) return NULL;
    
    CardNode *cur = d->head;
    for (int i = 0; i < index && cur; i++) {
        cur = cur->next;
    }
    return cur;
}

// Retorna quantas cartas tem
int deck_size(const Deck *d) {
    return d ? d->size : 0;
}

// Mostra todas cartas do deck
void deck_display(Deck *d) {
    if (!d) return;
    
    printf("\n--- BARALHO DISPONIVEL ---\n");
    CardNode *cur = d->head;
    int count = 1;
    
    while (cur) {
        printf("%2d: %c%c  ", count++, cur->card.value, cur->card.suit);
        if ((count - 1) % 4 == 0) printf("\n");
        cur = cur->next;
    }
    printf("-------------------------\n");
}