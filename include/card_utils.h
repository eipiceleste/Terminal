#ifndef CARD_UTILS_H
#define CARD_UTILS_H

#include "deck.h"

// Compara dois naipes: retorna quem ganha
// 1 = suit1 vence, 0 = empate, -1 = suit2 vence
// Hierarquia: H(♥) > C(♣) > D(♦) > S(♠) > H
int compare_suits(char suit1, char suit2);

// Converte valor da carta pra nome (A → "As")
void value_to_name(char value, char *name);

// Mostra carta: se revelada mostra "A♥", senão "[?] "
void print_card_simple(Card card);

// OBSERVAÇÃO: analyze_guess() também está em card_utils.c
// mas foi declarada errado aqui (tá em minigame_cards.h)

#endif