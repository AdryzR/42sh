/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_which.c
*/

#include "my_sh.h"

static void check_which(shell_t *shell, char *co, int *state)
{
    if (is_a_built_in(shell, co, false) == 0) {
        printf("%s: shell built-in command.\n", co);
        free(co);
        return;
    }
    (*state) = check_commands(shell, co, true);
    if ((*state) == 84) {
        shell->shell_status = 1;
        free(co);
        return;
    }
    for (int i = 0; co[i]; ++i)
        if (co[i] == '/') {
            printf("%s\n", co);
            free(co);
            return;
        }
    printf("%s\n", shell->full_path);
    free(co);
    return;
}

int my_which(shell_t *shell)
{
    int state = 0;
    char *command;

    shell->shell_status = 0;
    if (!shell->command[1]) {
        shell->shell_status = 1;
        my_putstr_ch(2, "which: Too few arguments.\n");
        return 84;
    }
    for (int i = 1; shell->command[i]; ++i) {
        command = strdup(shell->command[i]);
        check_which(shell, command, &state);
    }
    return state;
}
