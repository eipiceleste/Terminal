#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "utils.h"

// Pega uma resposta do teclado (número ou ESC)
// Retorna 0 se apertar ESC, senão retorna o número
int answer() {
    char c = _getch();  // Pega tecla sem esperar Enter
    if (c == 27) return 0;  // 27 = ESC
    int opc = c - '0';  // Converte char pra int ('1' -> 1)
    printf("\n\n");
    Sleep(200);  // Pequena pausa
    return opc;
}

// Apaga o arquivo de save (se existir)
void clear_save_file(void) {
    FILE *f = fopen("data/save.dat", "w");
    if (f != NULL) {
        fclose(f);  // Só abre e fecha em modo "w" já limpa
    }
}