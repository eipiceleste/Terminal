#ifndef SAVE_H
#define SAVE_H

#include "game_state.h"

// Salva estado do jogo em data/save.dat
// Retorna 1 se deu certo, 0 se falhou
// Chamado automaticamente quando ganha minigame
int game_save(GameState *gs, const char *filename);

// Carrega estado do jogo de data/save.dat  
// Retorna 1 se carregou, 0 se falhou (arquivo não existe)
int game_load(GameState *gs, const char *filename);

#endif