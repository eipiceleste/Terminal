#ifndef UTILS_H
#define UTILS_H

// Pega tecla do usuário (número 1-9 ou ESC)
// Retorna 0 se apertou ESC, número se apertou 1-9
// Usada em TODOS os menus: menu principal, diálogo, minigame
int answer();

// Apaga o arquivo de save (data/save.dat)
// Chamado só quando começa jogo novo
void clear_save_file(void);

#endif