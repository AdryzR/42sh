/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** history_gest
*/

#include "my_sh.h"
#include "my.h"

int history_up(shell_t *shell, int index)
{
    char *line = NULL;
    FILE *file = fopen(".history.txt", "r");

    if (!file)
        return ret_and_set_status(84, shell);
    index--;
    if (index == 0)
        return 0;
    fread(&line, index, 0, file);
    fclose(file);
    return index;
}

int history_down(shell_t *shell, history_t *hist, int index)
{
    char *line = NULL;
    FILE *file = fopen(".history.txt", "r");

    if (!file)
        return ret_and_set_status(84, shell);
    index++;
    if (index == hist->index)
        return 0;
    fread(&line, index, 0, file);
    fclose(file);
    return index;
}

int history_gest(shell_t *shell, history_t *hist)
{
    FILE *ptr;

    ptr = fopen(".history.txt", "a");
    if (!ptr)
        return ret_and_set_status(84, shell);
    fprintf(ptr, shell->line, "%s\n");
    fclose(ptr);
    hist->index++;
    return 0;
}
