#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "deck.h"

#define CODE_LENGTH 4       // Mesmo do minigame
#define MAX_ATTEMPTS 8      // Mesmo do minigame  
#define NAME_LENGTH 20      // Mesmo do deck

// Estados possíveis do jogo (máquina de estados)
typedef enum {
    STATE_MENU,      // Menu principal
    STATE_DIALOGUE,  // Conversando com NPC
    STATE_MINIGAME,  // Jogando minigame de cartas
    STATE_INVENTORY, // NÃO IMPLEMENTADO (tela de inventário)
    STATE_EXIT       // Saindo do jogo
} GameMode;

// Dados do minigame que são salvos
typedef struct {
    Card secret[CODE_LENGTH];   // Código secreto atual
    int deck_indices[NUM_CARDS]; // Indices das cartas no baralho
    int deck_size;              // Quantas cartas restam
    int attempts;               // Tentativas usadas (0-8)
    int score;                  // Pontuação (não usada pra nada)
    int completed;              // 1 se já completou o minigame
} MiniGameSave;

// Informações do jogador
typedef struct {
    int clues_found;           // Pistas encontradas (incrementa quando ganha minigame)
    char inventory[100];       // Itens do inventário (NÃO IMPLEMENTADO)
    char name[50];             // Nome do jogador (definido no diálogo)
} Player;

// Estado completo do jogo (o que é salvo)
typedef struct {
    GameMode mode;             // Em que tela está
    Player player;             // Info do jogador
    MiniGameSave minigame_save; // Progresso do minigame
    Deck* minigame_deck;       // Baralho atual (NÃO é salvo, é recriado)
} GameState;

// Inicializa estado do jogo (valores padrão)
void init_gamestate(GameState *gs);

// Loop principal do jogo (chama telas baseado no modo)
void gameloop(GameState *gs);

// Debug: mostra estado na tela (usado quando carrega save)
void debug_print(GameState *gs);

// Libera memória alocada (baralho e diálogos)
void free_gamestate(GameState *gs);

// Recria baralho a partir dos dados salvos (índices)
// Necessário porque ponteiros não podem ser salvos
void rebuild_deck_from_save(GameState *gs);

#endif