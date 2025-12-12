#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "game_state.h"

#define MAX_TEXT_LENGTH 1024  // Máximo de caracteres numa fala
#define MAX_OPTIONS 4         // Máximo de escolhas por diálogo

// Uma opção que o jogador pode escolher
typedef struct {
    char *text;           // Texto mostrado pro jogador
    int next_node;        // Pra qual nó vai se escolher isso (-1 = fim)
    int leads_to_minigame; // 1 se essa opção leva pro minigame de cartas
} DialogueOption;

// Um pedaço de conversa (uma "tela" de diálogo)
typedef struct {
    int node_id;          // Número único do nó (começa em 0)
    char *text;          // O que o NPC fala (pode ter [NOME])
    int num_options;     // Quantas opções tem (1-4)
    DialogueOption options[MAX_OPTIONS]; // Opções disponíveis
} DialogueNode;

// Carrega diálogos de data/dialogue.dat (arquivo binário)
// O arquivo precisa ser criado por um editor separado pra funcionar e virar .dat então pedi pra um amigo (rafael obrigado) fazer aquele código em python
void dialogue_load(const char *filename);

// Inicia o sistema de diálogo (chamado do menu_dialogue.c)
void dialogue_start(GameState *gs);

// Mostra o nó atual e gerencia escolhas (usada internamente)
void dialogue_show_current(GameState *gs);

// Libera memória dos diálogos (chamado quando jogo termina)
void dialogue_free(void);  

#endif