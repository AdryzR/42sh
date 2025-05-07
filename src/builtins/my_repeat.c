/*
** EPITECH PROJECT, 2024
** B-PSU-200-STG-2-1-42sh-adrien.raphanaud
** File description:
** my_repeat.c
*/

#include "my_sh.h"
#include "parser.h"
#include "interpreter.h"

static void repeat_loop(int n, shell_t *shell, char *line)
{
    lexer_t lexer = { 0 };
    ast_t *ast;

    for (int i = n; i > 0; i--) {
        lexer = update_lexer(lexer, line);
        ast = parser_parse(&lexer);
        if (!ast) {
            shell->shell_status = 1;
            continue;
        }
        interpret(ast, shell);
        free_ast(ast);
    }
}

static int manage_error(shell_t *shell)
{
    if (!shell->command[1] || !shell->command[2]) {
        shell->shell_status = 1;
        my_putstr_ch(2, "repeat: Too few arguments.\n");
        return 84;
    }
    if (my_str_isnum(shell->command[1]) == 0) {
        shell->shell_status = 1;
        my_putstr_ch(2, "repeat: Badly formed number.\n");
        return 84;
    }
    return 0;
}

int my_repeat(shell_t *shell)
{
    int n = 0;
    int k = 0;
    char *line = NULL;

    if (manage_error(shell) == 84)
        return 84;
    n = my_getnbr(shell->command[1]);
    line = word_array_to_str(shell->command, " ", 2);
    free_array(shell->command);
    shell->command = NULL;
    repeat_loop(n, shell, line);
    free(line);
    return 0;
}
