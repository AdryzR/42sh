/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** history
*/

#include "my_sh.h"

void set_index(shell_t *shell, history_t *hist)
{
    FILE *file = fopen(".history", "r");

    if (!file) {
        fopen(".history", "w");
        return;
    }
    hist->index = 0;
    for (int c = 0; (c = fgetc(file)) != EOF;) {
        if (c == '\n')
            hist->index++;
    }
    printf("index set at: %d\n", hist->index);
    fclose(file);
}
