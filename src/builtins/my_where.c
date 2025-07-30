/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_where.c
*/

#include "my_sh.h"

static void print_tab_n(char **tab, int i)
{
    for (; tab[i]; ++i)
        printf("/%s", tab[i]);
    printf("\n");
}

static void free_check_where(char **to_free, char *cmd_to_free)
{
    free_array(to_free);
    free(cmd_to_free);
}

static void check_where(shell_t *shell, char *cmd, int *state)
{
    char **temp = NULL;
    char buffer[4096] = {0};
    int b = 1;

    if (is_a_built_in(shell, cmd, false) == 0) {
        printf("%s is a shell built-in\n", cmd);
        b = 0;
    }
    (*state) = check_commands(shell, cmd, false);
    if ((*state) == 84) {
        shell->shell_status = b;
        return (void)free(cmd);
    }
    temp = my_str_to_word_array(shell->path_copy, ":");
    for (int i = 0; temp[i]; i++) {
        snprintf(buffer, sizeof(buffer), "%s/%s", temp[i], cmd);
        if (!access(buffer, X_OK))
            dprintf(1, "%s\n", buffer);
    }
    free_check_where(temp, cmd);
}

static int check_path(shell_t *shell, char *command)
{
    for (int i = 0; command[i]; ++i)
        if (command[i] == '/') {
            shell->shell_status = 1;
            my_putstr_ch(2, "where: / in command makes no sense\n");
            return 84;
        }
    return 0;
}

int my_where(shell_t *shell)
{
    int state = 0;
    char *command;

    shell->shell_status = 0;
    if (!shell->command[1]) {
        shell->shell_status = 1;
        my_putstr_ch(2, "where: Too few arguments.\n");
        return 84;
    }
    for (int i = 1; shell->command[i]; ++i) {
        if (check_path(shell, shell->command[i]) == 84)
            continue;
        command = strdup(shell->command[i]);
        check_where(shell, command, &state);
    }
    return state;
}
