/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** init_struct
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

void setup_path_copy(shell_t *shell)
{
    envi_t *buff = shell->envi;

    for (; buff &&
        my_strncmp(buff->env, "PATH=", 5) != 0; buff = buff->next);
    if (!buff || !buff->parts[1])
        return;
    shell->path_copy = my_strdup(buff->parts[1]);
}

void add_env_line(char *env, shell_t *shell)
{
    envi_t *head = shell->envi;
    envi_t *new_node = NULL;

    if (!env)
        my_exit(shell, 84);
    new_node = malloc(sizeof(envi_t));
    if (!new_node)
        my_exit(shell, 84);
    new_node->env = my_strdup(env);
    new_node->parts = my_str_to_word_array(new_node->env, "=");
    new_node->next = shell->envi;
    new_node->prev = NULL;
    if (new_node->next)
        new_node->next->prev = new_node;
    shell->envi = new_node;
}

void init_pwd(shell_t *shell)
{
    envi_t *buff = shell->envi;

    for (; buff && my_strcmp(buff->parts[0], "HOME") != 0;
        buff = buff->next);
    if (!buff)
        return;
    shell->home = my_strdup(buff->parts[1]);
    for (buff = shell->envi; buff && my_strcmp(buff->parts[0], "OLDPWD") != 0;
        buff = buff->next);
    if (!buff)
        return;
    shell->old_pwd = my_strdup(buff->parts[1]);
}

void save_fd(shell_t *shell)
{
    shell->saved_fds[0] = -1;
    shell->saved_fds[1] = -1;
}

static void init_alias(shell_t *shell)
{
    shell->aliases = NULL;
}

void init_struct(shell_t *shell, char **env)
{
    *shell = (shell_t){ 0 };
    init_alias(shell);
    for (int i = 0; env[i]; i++)
        add_env_line(env[i], shell);
    init_pwd(shell);
    save_fd(shell);
    setup_path_copy(shell);
}
