#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"
#include "utils.h"

// Variáveis globais do sistema de diálogo
static DialogueNode *dialogue_tree = NULL;  // Árvore de diálogos carregada
static int total_nodes = 0;                 // Quantos nós tem
static int current_node = 0;                // Nó atual na conversa
static char player_name[50] = "";           // Nome do jogador guardado aqui

// Pede nome do jogador no começo do diálogo
void read_player_name(GameState *gs) {
    printf("\n\nINSIRA SEU NOME: ");
    
    char name[50];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;  // Remove o \n do final
    
    if (strlen(name) > 0) {
        strncpy(gs->player.name, name, 49);
        gs->player.name[49] = '\0';
        strcpy(player_name, name);
    } else {
        strcpy(gs->player.name, "ALICE");
        strcpy(player_name, "ALICE");
    }
    
    printf("\nNOME REGISTRADO: %s\n", gs->player.name);
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n');
}

// Limpa toda a memória dos diálogos
void dialogue_free(void) {
    if (!dialogue_tree) return;
    
    for (int i = 0; i < total_nodes; i++) {
        if (dialogue_tree[i].text) {
            free(dialogue_tree[i].text);
        }
        for (int j = 0; j < dialogue_tree[i].num_options; j++) {
            if (dialogue_tree[i].options[j].text) {
                free(dialogue_tree[i].options[j].text);
            }
        }
    }
    free(dialogue_tree);
    dialogue_tree = NULL;
    total_nodes = 0;
    current_node = 0;
}

// Carrega diálogo de arquivo binário
void dialogue_load(const char *filename) {
    dialogue_free();
    
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Erro ao carregar dialogo: %s\n", filename);
        return;
    }
    
    // Lê quantos nós tem
    fread(&total_nodes, sizeof(int), 1, f);
    
    // Aloca memória para todos os nós
    dialogue_tree = (DialogueNode*)calloc(total_nodes, sizeof(DialogueNode));
    if (!dialogue_tree) {
        printf("ERRO: Falha ao alocar memoria!\n");
        fclose(f);
        return;
    }
    
    char buffer[MAX_TEXT_LENGTH];
    
    // Lê cada nó do arquivo
    for (int i = 0; i < total_nodes; i++) {
        fread(&dialogue_tree[i].node_id, sizeof(int), 1, f);
        
        // Lê texto do NPC
        fread(buffer, sizeof(char), MAX_TEXT_LENGTH, f);
        buffer[MAX_TEXT_LENGTH-1] = '\0';
        
        int len = strnlen(buffer, MAX_TEXT_LENGTH);
        dialogue_tree[i].text = (char*)malloc(len + 1);
        if (dialogue_tree[i].text) {
            strcpy(dialogue_tree[i].text, buffer);
        }
        
        fread(&dialogue_tree[i].num_options, sizeof(int), 1, f);
        
        // Lê cada opção deste nó
        for (int j = 0; j < dialogue_tree[i].num_options; j++) {
            fread(buffer, sizeof(char), MAX_TEXT_LENGTH, f);
            buffer[MAX_TEXT_LENGTH-1] = '\0';
            
            len = strnlen(buffer, MAX_TEXT_LENGTH);
            dialogue_tree[i].options[j].text = (char*)malloc(len + 1);
            if (dialogue_tree[i].options[j].text) {
                strcpy(dialogue_tree[i].options[j].text, buffer);
            }
            
            fread(&dialogue_tree[i].options[j].next_node, sizeof(int), 1, f);
            fread(&dialogue_tree[i].options[j].leads_to_minigame, sizeof(int), 1, f);
        }
    }
    
    fclose(f);
    printf("Dialogo carregado: %d nos\n", total_nodes);
}

// Mostra o nó atual de diálogo na tela
void dialogue_show_current(GameState *gs) {
    if (!dialogue_tree || current_node >= total_nodes) {
        printf("Erro: Dialogo nao carregado.\n");
        return;
    }
    
    DialogueNode *node = &dialogue_tree[current_node];
    
    // Prepara texto, substituindo [NOME] pelo nome real
    char display_text[MAX_TEXT_LENGTH];
    strcpy(display_text, node->text);
    
    // Se tiver [NOME] no texto, troca pelo nome do jogador
    if (strstr(display_text, "[NOME]") && strlen(player_name) > 0) {
        char temp[MAX_TEXT_LENGTH];
        char *pos = strstr(display_text, "[NOME]");
        
        int idx = pos - display_text;
        strncpy(temp, display_text, idx);
        temp[idx] = '\0';
        
        strcat(temp, player_name);
        strcat(temp, pos + 6);
        
        strcpy(display_text, temp);
    }
    
    printf("\n%s\n\n", display_text);
    
    // Mostra as opções
    for (int i = 0; i < node->num_options; i++) {
        printf("%d - %s\n", i + 1, node->options[i].text);
    }
    printf("ESC - Voltar ao menu\n");
}

// Loop principal do diálogo
void dialogue_start(GameState *gs) {
    // Carrega se ainda não carregou
    if (!dialogue_tree) {
        dialogue_load("data/dialogue.dat");
    }
    
    current_node = 0;
    
    while (1) {
        system("cls");
        dialogue_show_current(gs);
        
        int choice = answer();
        
        if (choice == 0) {  // ESC - volta ao menu
            gs->mode = STATE_MENU;
            return;
        }
        
        DialogueNode *node = &dialogue_tree[current_node];
        
        // Nó especial: primeiro nó pede nome
        if (current_node == 0 && choice == 1) {
            read_player_name(gs);
            current_node = 1;
            continue;
        }
        
        if (choice < 1 || choice > node->num_options) {
            printf("Opcao invalida!\n");
            continue;
        }
        
        DialogueOption *opt = &node->options[choice - 1];
        
        // Opção que leva pro minigame
        if (opt->leads_to_minigame) {
            gs->mode = STATE_MINIGAME;
            return;
        }
        
        // Opção que termina diálogo
        if (opt->next_node == -1) {
            printf("\nFim da conversa.\n");
            printf("Pressione Enter para voltar...");
            while (getchar() != '\n');
            gs->mode = STATE_MENU;
            return;
        }
        
        // Vai pro próximo nó
        current_node = opt->next_node;
    }
}