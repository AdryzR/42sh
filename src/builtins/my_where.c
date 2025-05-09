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

static void check_where(shell_t *shell, char *co, int *state)
{
    char **temp = NULL;
    int b = 1;

    if (is_a_built_in(shell, co, false) == 0 || strcmp(co, "echo") == 0) {
        printf("%s is a shell built-in\n", co);
        b = 0;
    }
    (*state) = check_commands(shell, co, false);
    if ((*state) == 84) {
        shell->shell_status = b;
        free(co);
        return;
    }
    temp = my_str_to_word_array(shell->full_path, "/\n");
    for (int i = 0; strcmp(temp[i], co) != 0; ++i)
        print_tab_n(temp, i);
    free_array(temp);
    free(co);
    return;
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
