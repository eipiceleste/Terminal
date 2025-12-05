#include <stdio.h>
#include "menu_minigame.h"
#include "utils.h"
#include "save.h"

void minigame_screen(GameState *gs)
{
    printf("\n\n MENU_MINIGAME MINIGAME_SCREEN\n");
    printf("1 - Voltar para o MENU_DIALOGO\n");
    printf("2 - DEBUG incrementar clues\n");
    printf("3 - DEBUG liberar nova clue\n");
    printf("4 - Salvar e sair\n");
    printf("ESC - Voltar para o menu principal\n");

    int opc = answer();

    switch (opc)
    {
    case 0:
        gs->mode = STATE_MENU;
        break;
    case 1:
        gs->mode = STATE_DIALOGUE;
        break;
    case 2: // DEBUG adicionar clue
        gs->player.clues_found++;
        printf("Clue adicionada. Total: %d\n", gs->player.clues_found);
        break;
    case 3:
    { // DEBUG liberar nova clue
        FILE *f = fopen("pistas/pista_teste.dat", "w");
        if (!f)
        {
            printf("Erro\n");
            break;
        }
        char *texto = "teste oi isso e uma pista";
        for (int i = 0; texto[i]; i++)
        {
            fputc(texto[i] + 3, f);
        }
        fclose(f);

        printf("Nova pista encontrada\n");
        printf("Digite o Codigo da Pista para liberar no inventario: \n");

        int cod = 0;
        scanf("%d", &cod);

        if (cod != 1234)
        {
            printf("Codigo incorreto.\n");
        }
        else
        {
            FILE *f2 = fopen("pistas/pista_teste.dat", "r");
            int c;
            while ((c = fgetc(f2)) != EOF)
            {
                putchar(c - 3);
            }
            fclose(f2);
            printf("\nPista liberada no inventario.\n");
        }

        break;
    }
    case 4:
        if (save_game(gs, "data/save.dat"))
        {
            printf("Jogo salvo\n");
        }
        gs->mode = STATE_MENU;
        break;
    default:
        printf("Opcao invalida\n");
        break;
    }
}