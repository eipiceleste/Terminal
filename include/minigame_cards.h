#ifndef MINIGAME_CARDS_H
#define MINIGAME_CARDS_H

#include "game_state.h"

// Prepara minigame novo (gera código secreto, etc)
void minigame_init(GameState *gs);

// Recria baralho quando carrega save (chamado de game_state.c)
void rebuild_deck_from_save(GameState *gs);

// Executa uma rodada (pede palpite, analisa, mostra resultado)
void minigame_play_round(GameState *gs);

// Analisa palpite compara com código secreto
// Retorna acertos posição/valor, vitórias naipe
// Implementada em card_utils.c porque lida só com cartas
void analyze_guess(Card secret[], Card guess[], int *correct_pos,
                  int *correct_val, int *player_wins, int *computer_wins);

// Verifica se escolha é válida (4 cartas diferentes)
int validate_choice(Deck *d, int choices[], Card guess[]);

// Tela principal do minigame (loop com tentativas)
void iniciar_minigame_cartas(GameState *gs);

// Mostra código secreto quando perde
void display_minigame_result(GameState *gs);

// Gera código secreto aleatório (4 cartas diferentes)
void generate_secret_code(Deck *d, Card secret[]);

// Converte baralho pra array de índices (pra salvar)
void deck_to_indices(Deck *d, int indices[]);

#endif