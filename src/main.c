/*
** EPITECH PROJECT, 2025
** B-CPE-110-STG-1-1-secured-mateo.antoni-christ
** File description:
** secured
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_printf.h"
#include "my_sh.h"

static void handle_sigint(__attribute__((unused)) int sig)
{
    my_putstr("\n> ");
}

static void getline_end(shell_t *shell)
{
    shell->nb_args = 0;
    my_exit(shell, CURRENT_STATUS);
}

static void count_pipes(shell_t *shell)
{
    shell->nb_pipes = 0;
    for (int i = 0; shell->line[i]; i++)
        if (shell->line[i] == '|')
            shell->nb_pipes++;
}

int setup_args(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, ";");

    if (!commands)
        return 84;
    free(shell->line);
    for (int i = 0; commands[i]; i++) {
        shell->line = commands[i];
        count_pipes(shell);
        handle_pipes(shell);
    }
    free_array(commands);
    shell->line = NULL;
    return 0;
}

int while_loop(shell_t *shell, char **env, history_t *history)
{
    signal(SIGINT, handle_sigint);
    while (42) {
        set_index(shell, history);
        write(0, "> ", 2);
        getinput_gest(shell, env);
        history_gest(shell, history);
        if (shell->line[0] == '\0')
            continue;
        setup_args(shell);
    }
}

int main(int ac, char **av, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (init_struct(shell, env))
        return 84;
    while_loop(shell, env, shell->history);
    return 0;
}
