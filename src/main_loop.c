/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main_loop
*/

#include <my_sh.h>
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

static void update_args(shell_t *shell, ssize_t bytes_read)
{
    shell->nb_args = 0;
    setup_path_copy(shell);
    if (bytes_read == -1)
        my_exit(shell, CURRENT_STATUS);
}

void main_loop(shell_t *shell)
{
    size_t args_len = 0;
    ssize_t bytes_read = 0;
    ast_t *ast;
    lexer_t lexer = { 0 };

    for (;;) {
        print_prompt_if_tty(shell);
        bytes_read = getline(&shell->line, &args_len, stdin);
        update_args(shell, bytes_read);
        if (my_strcmp(shell->line, "\n") == 0)
            continue;
        lexer = update_lexer(lexer, shell->line);
        ast = parser_parse(&lexer);
        if (!ast) {
            shell->shell_status = 1;
            continue;
        }
        interpret(ast, shell);
        free_ast(ast);
    }
}
