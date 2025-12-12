#include <stdio.h>
#include "card_ui.h"

// Mostra regras do minigame
void display_rules_simple(void) {
    printf("\n=== DESCRIPTOGRAFIA CARTA ===\n");
    printf("Decifre 4 cartas em ate 8 tentativas\n");
    printf("Cartas: A, J, Q, K | Naipes: H, C, D, S\n");
    printf("Hierarquia: H > C > D > S > H\n");
    printf("Feedback: posicoes corretas, valores, vitorias de naipe\n");
}