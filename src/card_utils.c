#include <stdio.h>
#include <string.h>
#include "card_utils.h"

// Converte valor da carta pra nome (A -> "As")
void value_to_name(char value, char *name) {
    switch (value) {
        case 'A': strcpy(name, "As"); break;
        case 'J': strcpy(name, "Valete"); break;
        case 'Q': strcpy(name, "Rainha"); break;
        case 'K': strcpy(name, "Rei"); break;
        default: strcpy(name, "?"); break;
    }
}

// Mostra carta: se revelada mostra valor+naipe, senão [?]
void print_card_simple(Card card) {
    if (card.revealed) printf("%c%c ", card.value, card.suit);
    else printf("[?] ");
}

// Compara naipes: H(♥) > C(♣) > D(♦) > S(♠) > H
int compare_suits(char suit1, char suit2) {
    if (suit1 == suit2) return 0;
    
    if ((suit1 == 'H' && suit2 == 'C') ||
        (suit1 == 'C' && suit2 == 'D') ||
        (suit1 == 'D' && suit2 == 'S') ||
        (suit1 == 'S' && suit2 == 'H')) {
        return 1; // suit1 vence (Explicando, uma carta só vence de uma outra, e perde para todas as outras permitindo você fazer uma comparação de empate)
    }
    return -1; // suit2 vence (Explicando também que as cartas só tretam com aquela na mesma posição)
}

// Analisa palpite: compara com código secreto
// Isso é o coração do minigame pro feedback lógico
void analyze_guess(Card secret[], Card guess[], int *correct_pos, 
                   int *correct_val, int *player_wins, int *computer_wins) {
    *correct_pos = *correct_val = *player_wins = *computer_wins = 0;
    
    // Marca quais cartas já foram "usadas" na comparação
    int secret_used[CODE_LENGTH] = {0};
    int guess_used[CODE_LENGTH] = {0};
    
    // Primeiro: acertos exatos (mesma carta na mesma posição)
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i].value == secret[i].value && 
            guess[i].suit == secret[i].suit) {
            (*correct_pos)++;
            secret[i].revealed = 1;  // Revela carta correta
            secret_used[i] = 1;
            guess_used[i] = 1;
        }
    }
    
    // Segundo: valores corretos mas posição errada
    // (não conta cartas já acertadas exatamente)
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess_used[i]) continue;  // Já acertou exato
        
        for (int j = 0; j < CODE_LENGTH; j++) {
            if (secret_used[j]) continue;  // Esta do secret já foi usada
            
            if (guess[i].value == secret[j].value) {
                (*correct_val)++;
                secret_used[j] = 1;
                guess_used[i] = 1;
                break;  // Só conta uma vez por carta
            }
        }
    }
    
    // Terceiro: comparação de naipes
    for (int i = 0; i < CODE_LENGTH; i++) {
        int result = compare_suits(guess[i].suit, secret[i].suit);
        if (result == 1) {
            (*player_wins)++;
        } else if (result == -1) {
            (*computer_wins)++;
        }
        // Empate não conta dai tu consegue entender que aquela carta tá ali mesmo
    }
}