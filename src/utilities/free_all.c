/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_all
*/

#include <my_sh.h>

//TODO: free les choses que j'ai rajouté à la struct
void free_str(char *str)
{
    if (str)
        free(str);
}

static void free_aliases(shell_t *shell)
{
    alias_t *buff = NULL;

    while (shell->aliases) {
        buff = shell->aliases;
        free(buff->name);
        free(buff->cmd);
        shell->aliases = shell->aliases->next;
        free(buff);
    }
    free(shell->aliases);
}

static void free_env(shell_t *shell)
{
    envi_t *buff = NULL;

    while (shell->envi) {
        buff = shell->envi;
        free(buff->env);
        free_array(buff->parts);
        shell->envi = shell->envi->next;
        free(buff);
    }
    free(shell->envi);
}

void free_all(shell_t *shell)
{
    free_env(shell);
    free_str(shell->line);
    free_array(shell->command);
    free_str(shell->path_copy);
    free_str(shell->full_path);
    free_str(shell->home);
    free_str(shell->old_pwd);
    if (shell != NULL)
        free(shell);
}
