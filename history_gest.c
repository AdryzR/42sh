/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** history_gest
*/

#include "my_sh.h"
#include "my.h"

int history_up(shell_t *shell)
{
    FILE *file = fopen(".history.txt", "r");

    if (!file)
        return ret_and_set_status(84, shell);
    fclose(file);
}

int history_down(shell_t *shell)
{

}

int history_gest(shell_t *shell)
{
    FILE *ptr;

    ptr = fopen(".history.txt", "a");
    if (!ptr)
        return ret_and_set_status(84, shell);
    fprintf(ptr, shell->line, "%s\n");
    fclose(ptr);
    remove(".history.txt");
    return 0;
}
