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

static void handle_sigint(__attribute__((unused)) int sig)
{
    my_putstr("\n$> ");
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

static int check_cond(shell_t *shell, ssize_t byte_read, size_t args_len)
{
    // if (isatty(0) == 1)
    //     print_prompt(shell->envi);
    byte_read = getline(&shell->line, &args_len, stdin);
    if (byte_read == -1)
        getline_end(shell);
    if (my_strcmp(shell->line, "\n") == 0)
        return 0;
}
int getline_gest(shell_t *shell, char **env)
{
    int c;
    ssize_t byte_read = 0;
    size_t args_len = 0;

    if (!shell)
        return 84;
    init_struct(shell, env);
    if (isatty(STDIN_FILENO))
        my_putstr("$> ");
    byte_read = getline(&shell->line, &args_len, stdin);
    if (byte_read == -1)
        exit(84);
    if (shell->line[byte_read - 1] == '\n')
        shell->line[byte_read - 1] = '\0';
    return 0;
}

int while_loop(shell_t *shell, char **env)
{
    signal(SIGINT, handle_sigint);
    while (1) {
        getline_gest(shell, env);
        if (shell->line[0] == '\0') {
            my_putstr("\n");
            continue;
        }
        arrows_key(shell, shell->history);
        history_gest(shell, shell->history);
        clean_line(shell);
        setup_args(shell);
    }
}

int main(int ac, char **av, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (init_struct(shell, env))
        return 84;
    while_loop(shell, env);
    return 0;
}
