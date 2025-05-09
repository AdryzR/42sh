/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_argument
*/

#include <my_sh.h>

static int glob_error(glob_t *to_free, int ret)
{
    globfree(to_free);
    return 84;
}

int interpret_argument(const ast_t *ast, shell_t *shell)
{
    glob_t glb = globbing(ast->data.arg);
    size_t matches = glb.gl_pathc;
    size_t to_add = matches ? matches : 1;
    size_t old = len_array(shell->command);
    size_t total = old + to_add + 1;
    char **tmp = (shell->command ? reallocarray(shell->command, total,
        sizeof(*tmp)) : calloc(total, sizeof(*tmp)));

    if (!tmp)
        return glob_error(&glb, 84);
    shell->command = tmp;
    if (matches) {
        for (size_t i = 0; i < matches; ++i)
            shell->command[old + i] = strdup(glb.gl_pathv[i]);
    } else {
        shell->command[old] = strdup(ast->data.arg);
    }
    shell->command[old + to_add] = NULL;
    globfree(&glb);
    return 0;
}
