/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** aliases
*/

#include "my.h"
#include "my_sh.h"

static char *concatenate_args(char **args)
{
    size_t len = 0;
    char *result;
    int i;

    if (args == NULL)
        return NULL;
    for (i = 0; args[i]; i++)
        len += strlen(args[i]) + 1;
    result = malloc(len);
    if (!result)
        return NULL;
    result[0] = '\0';
    for (i = 0; args[i]; i++) {
        strcat(result, args[i]);
        if (args[i + 1])
            strcat(result, " ");
    }
    return result;
}

static char *get_alias_value(alias_t *head, const char *name)
{
    if (name == NULL)
        return NULL;
    for (; head != NULL; head = head->next) {
        if (head->name != NULL && strcmp(head->name, name) == 0)
            return head->cmd;
    }
    return NULL;
}

static void free_aliases(alias_t *head)
{
    alias_t *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp->cmd);
        free(tmp);
    }
}

int is_valid_alias_command(shell_t *shell)
{
    if (shell == NULL || shell->nb_args < 1 || shell->command == NULL ||
        strcmp(shell->command[0], "alias") != 0)
        return 0;
    return 1;
}

int handle_single_alias(shell_t *shell)
{
    if (shell->nb_args == 1)
        return print_alias(shell->aliases, shell);
    return 1;
}

int handle_double_alias(shell_t *shell)
{
    if (shell->command[1] == NULL) {
        fprintf(stderr, "alias: missing argument\n");
        return 1;
    }
    return print_alias(shell->aliases, shell);
}

int handle_multiple_aliases(shell_t *shell)
{
    char *cmd = NULL;

    if (shell->command[1] == NULL || shell->command[2] == NULL) {
        fprintf(stderr, "alias: missing arguments\n");
        return 1;
    }
    cmd = concatenate_args(shell->command + 2);
    if (!cmd)
        return 1;
    add_alias(&shell->aliases, shell->command[1], cmd);
    free(cmd);
    return 0;
}

int my_alias(shell_t *shell)
{
    if (!is_valid_alias_command(shell))
        return 1;
    if (shell->nb_args == 1)
        return handle_single_alias(shell);
    if (shell->nb_args == 2)
        return handle_double_alias(shell);
    if (shell->nb_args >= 3)
        return handle_multiple_aliases(shell);
    return 1;
}
