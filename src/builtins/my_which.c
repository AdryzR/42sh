/*
** EPITECH PROJECT, 2024
** B-PSU-200-STG-2-1-42sh-adrien.raphanaud
** File description:
** my_which.c
*/

#include "my_sh.h"

static void check_which(shell_t *shell, char *command, int *state)
{
    if (is_a_built_in(shell, command, false) == 0) {
        printf("%s: shell built-in command.\n", command);
        free(command);
        return;
    }
    (*state) = check_commands(shell, command, true);
    if ((*state) == 84) {
        shell->shell_status = 1;
        free(command);
        return;
    }
    for (int i = 0; command[i]; ++i)
        if (command[i] == '/') {
            printf("%s\n", command);
            free(command);
            return;
        }
    printf("%s\n", shell->full_path);
    free(command);
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
