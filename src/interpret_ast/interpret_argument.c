/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_argument
*/

#include <my_sh.h>

int interpret_argument(const ast_t *ast, shell_t *shell)
{
    size_t array_size;

    if (!shell->command) {
        shell->command = calloc(2, sizeof(char *));
        if (!shell->command)
            return 84;
        shell->command[0] = strdup(ast->data.arg);
        return 0;
    }
    array_size = len_array(shell->command);
    shell->command = reallocarray(
        shell->command, array_size + 2, sizeof(char *)
    );
    shell->command[array_size] = strdup(ast->data.arg);
    shell->command[array_size + 1] = NULL;
    return 0;
}
