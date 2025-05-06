/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** history_gest
*/

#include "my_sh.h"
#include "my.h"

int history_up(shell_t *shell, history_t *hist)
{
    size_t len = 0;
    char *line = NULL;
    FILE *file = fopen(".history", "r");
    int size = 0;

    if (!file)
        return ret_and_set_status(84, shell);
    if (hist->index == 0)
        return 0;
    hist->index--;
    fgets(line, 1024, file);
    len = strlen(line);
    write(0, line, len);
    fclose(file);
    return 0;
}

int history_down(shell_t *shell, history_t *hist)
{
    size_t len = 0;
    char *line = NULL;
    FILE *file = fopen(".history", "r");

    if (!file)
        return ret_and_set_status(84, shell);
    hist->index++;
    if (hist->index == hist->index)
        return 0;
    fread(&line, hist->index, 0, file);
    len = strlen(line);
    write(0, line, len);
    fclose(file);
    return 0;
}

int history_gest(shell_t *shell, history_t *hist)
{
    FILE *ptr;

    ptr = fopen(".history", "a");
    if (!ptr)
        return ret_and_set_status(84, shell);
    fprintf(ptr, "%s\n", shell->line);
    fclose(ptr);
    hist->index++;
    return 0;
}
