/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main_loop
*/

#include <my_sh.h>
#include <interpreter.h>

static lexer_t update_lexer(lexer_t lexer, char *line)
{
    lexer_t new = {.start = line};

    return new;
}

static void print_prompt_if_tty(shell_t *shell)
{
    if (isatty(0) == 1)
        print_prompt(shell);
}

static void check_getline_end(shell_t *shell, ssize_t bytes_read)
{
    shell->nb_args = 0;
    if (bytes_read == -1)
        my_exit(shell, CURRENT_STATUS);
}

static int start_execution(shell_t *shell)
{
    ast_t *ast;
    lexer_t lexer = { 0 };

    lexer = update_lexer(lexer, shell->input);
    ast = parser_parse(&lexer);
    if (!ast) {
        shell->shell_status = 84;
        return 84;
    }
    interpret(ast, shell);
    free_ast(ast);
    free(shell->input);
    return 0;
}

void main_loop(shell_t *shell, ssize_t bytes_read)
{
    size_t args_len = 0;

    for (;;) {
        print_prompt_if_tty(shell);
        bytes_read = getline(&shell->line, &args_len, stdin);
        check_getline_end(shell, bytes_read);
        if (my_strcmp(shell->line, "\n") == 0)
            continue;
        shell->input = replace_aliases(shell, shell->line, shell->aliases);
        if (shell->input == NULL)
            continue;
        if (start_execution(shell) != 0)
            continue;
    }
}
