#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "deck.h"

// Salva estado do jogo em arquivo binário
int game_save(GameState *gs, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return 0;
    }
    
    // Salva versão (pra compatibilidade futura)
    int version = 1;
    fwrite(&version, sizeof(int), 1, f);
    
    // Salva GameState (todos os dados)
    // Não salva ponteiros, só os dados em si
    fwrite(&gs->mode, sizeof(GameMode), 1, f);
    fwrite(&gs->player, sizeof(Player), 1, f);
    fwrite(&gs->minigame_save, sizeof(MiniGameSave), 1, f);
    
    fclose(f);
    printf("Jogo salvo em %s\n", filename);
    return 1;
}

// Carrega estado do jogo
int game_load(GameState *gs, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Arquivo de save nao encontrado: %s\n", filename);
        return 0;
    }
    
    // Verifica versão do save
    int version;
    if (fread(&version, sizeof(int), 1, f) != 1) {
        printf("Erro ao ler versao do save.\n");
        fclose(f);
        return 0;
    }
    
    if (version != 1) {
        printf("Versao do save incompativel: %d\n", version);
        fclose(f);
        return 0;
    }
    
    // Carrega dados do GameState
    if (fread(&gs->mode, sizeof(GameMode), 1, f) != 1 ||
        fread(&gs->player, sizeof(Player), 1, f) != 1 ||
        fread(&gs->minigame_save, sizeof(MiniGameSave), 1, f) != 1) {
        printf("Erro ao ler dados do save.\n");
        fclose(f);
        return 0;
    }
    
    fclose(f);
    printf("Save carregado com sucesso.\n");
    return 1;
}