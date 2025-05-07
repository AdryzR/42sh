/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** history_gest
*/

#include "my_sh.h"
#include "my.h"

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
