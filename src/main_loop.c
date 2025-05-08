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

static void update_args(shell_t *shell)
{
    shell->nb_args = 0;
    setup_path_copy(shell);
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

void main_loop(shell_t *shell)
{
    size_t args_len = 0;

    for (;;) {
        set_index(shell, shell->history);
        print_prompt_if_tty(shell);
        shell->line = read_line(shell);
        history_gest(shell, shell->history);
        if (shell->line[0] == '\0')
            continue;
        update_args(shell);
        if (my_strcmp(shell->line, "\n") == 0)
            continue;
        shell->input = replace_aliases(shell, shell->line, shell->aliases);
        if (shell->input == NULL)
            continue;
        if (start_execution(shell) != 0)
            continue;
    }
}
