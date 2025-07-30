/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_gest
*/

#include "my_sh.h"
#include "my.h"

int history_gest(shell_t *shell, history_t *hist)
{
    FILE *ptr;

    if (strcmp(shell->line, "\n") == 0)
        return 0;
    ptr = fopen(".history", "a");
    if (!ptr)
        return 1;
    fprintf(ptr, "%s\n", shell->line);
    fclose(ptr);
    hist->index++;
    return 0;
}
