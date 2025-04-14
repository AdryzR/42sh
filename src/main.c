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

void print_prompt(char **env)
{
    char *user = my_getenv(env, "USER");
    char cwd[1000];

    user = my_strcat(user, "@");
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        write(1, "\033[0;32m", my_strlen("\033[0;32m"));
        write(1, user, my_strlen(user));
        write(1, "\033[0;36m", my_strlen("\033[0;36m"));
        write(1, cwd, my_strlen(cwd));
        write(1, "> ", 2);
        write(1, "\033[0m", my_strlen("\033[0m"));
    }
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
    char **commands = str_to_warray(shell->line, "^_^");

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

static void clean_line(shell_t *shell)
{
    if (shell->line[my_strlen(shell->line) - 1] == '\n')
        shell->line[my_strlen(shell->line) - 1] = '\0';
}

int main(int ac, char **av, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));
    size_t args_len = 0;
    ssize_t byte_read = 0;

    if (!shell)
        return 84;
    init_struct(shell, env);
    for (;;) {
        if (isatty(0) == 1)
            print_prompt(env);
        byte_read = getline(&shell->line, &args_len, stdin);
        if (byte_read == -1)
            getline_end(shell);
        if (my_strcmp(shell->line, "\n") == 0)
            continue;
        clean_line(shell);
        setup_args(shell);
    }
}
