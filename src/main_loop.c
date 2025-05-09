/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main_loop
*/

#include "my_sh.h"
#include <interpreter.h>

lexer_t update_lexer(lexer_t lexer, char *line)
{
    lexer_t new = {.start = line};

    return new;
}

static void print_prompt_if_tty(shell_t *shell)
{
    if (isatty(0) == 1)
        print_prompt(shell);
}

static void handle_sigint(__attribute__((unused)) int sig)
{
    shell_t shell = {0};

    my_putchar('\n');
    print_prompt_if_tty(&shell);
}

static void update_args(shell_t *shell, int bytes_read)
{
    shell->nb_args = 0;
    setup_path_copy(shell);
    if (!shell->line || bytes_read == -1)
        my_exit(shell, CURRENT_STATUS);
}

static int start_execution(shell_t *shell)
{
    ast_t *ast;
    lexer_t lexer = { 0 };

    lexer = update_lexer(lexer, shell->input);
    ast = parser_parse(&lexer);
    if (!ast) {
        shell->shell_status = 1;
        return 84;
    }
    interpret(ast, shell);
    free_ast(ast);
    free(shell->input);
    return 0;
}

static ssize_t get_input(shell_t *shell)
{
    size_t args_len = 0;

    if (isatty(0) == 0)
        return getline(&shell->line, &args_len, stdin);
    shell->line = read_line(shell);
    return 0;
}

void main_loop(shell_t *shell, ssize_t bytes_read)
{
    signal(SIGINT, handle_sigint);
    for (;;) {
        print_prompt_if_tty(shell);
        set_index(shell, shell->history);
        bytes_read = get_input(shell);
        if (shell->line[0] == '\n')
            continue;
        update_args(shell, bytes_read);
        if (shell->line[0] == '\0' || strcmp(shell->line, "exit") == 0)
            my_exit(shell, CURRENT_STATUS);
        history_gest(shell, shell->history);
        shell->input = replace_aliases(shell, shell->line, shell->aliases);
        if (shell->input == NULL)
            continue;
        if (start_execution(shell) != 0)
            continue;
    }
}
