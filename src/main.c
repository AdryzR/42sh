/*
** EPITECH PROJECT, 2025
** B-CPE-110-STG-1-1-secured-mateo.antoni-christ
** File description:
** secured
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_sh.h"
#include <lexer.h>
#include <parser.h>
#include <interpreter.h>

void print_prompt(void)
{
    printf("%s", getcwd(NULL, 0));
    printf("> ");
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
            print_prompt();
        byte_read = getline(&shell->line, &args_len, stdin);
        if (byte_read == -1)
            getline_end(shell);
        if (my_strcmp(shell->line, "\n") == 0)
            continue;
        lexer_t lexer = { .start = shell->line };
        lexer.pos = 0;
        ast_t *ast = parser_parse(&lexer);
        interpret(ast, shell);
        // clean_line(shell);
        // setup_args(shell);
    }
}


