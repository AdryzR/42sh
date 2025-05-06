/*
** EPITECH PROJECT, 2024
** B-PSU-200-STG-2-1-42sh-adrien.raphanaud
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

static void check_where(shell_t *shell, char *command, int *state)
{
    char **temp = NULL;

    if (is_a_built_in(shell, command, false) == 0) {
        printf("%s: shell built-in command.\n", command);
        free(command);
        return;
    }
    (*state) = check_commands(shell, command, false);
    if ((*state) == 84) {
        shell->shell_status = 1;
        free(command);
        return;
    }
    temp = my_str_to_word_array(shell->full_path, "/\n");
    for (int i = 0; strcmp(temp[i], command) != 0; ++i)
        print_tab_n(temp, i);
    free_array(temp);
    free(command);
    return;
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
    for (int i = 0; shell->command[1][i]; ++i)
        if (shell->command[1][i] == '/') {
            shell->shell_status = 1;
            my_putstr_ch(2, "where: / in command makes no sense\n");
            return 84;
        }
    for (int i = 1; shell->command[i]; ++i) {
        command = strdup(shell->command[i]);
        check_where(shell, command, &state);
    }
    return state;
}
