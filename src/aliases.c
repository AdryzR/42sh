/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** aliases
*/

#include "my.h"
#include "my_sh.h"

static int print_no_aliases(void)
{
    printf("No aliases defined.\n");
    return 0;
}

static int print_single_alias(const alias_t *alias)
{
    printf("%s\n", alias->cmd);
    return 0;
}

static int print_all_aliases(const alias_t *list)
{
    for (; list != NULL; list = list->next) {
        printf("%s\t\t%s\n", list->name, list->cmd);
    }
    return 0;
}

static int print_alias(alias_t *list, shell_t *shell)
{
    if (list == NULL)
        return print_no_aliases();
    if (shell->nb_args == 1)
        return print_all_aliases(list);
    if (shell->nb_args == 2 && shell->command[1] != NULL) {
        for (; list != NULL; list = list->next) {
            if (strcmp(list->name, shell->command[1]) == 0) {
                return print_single_alias(list);
            }
        }
    }
    return 0;
}

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

static void add_alias(alias_t **head, const char *name, const char *cmd)
{
    alias_t *tmp = *head;
    alias_t *new;

    if (name == NULL || cmd == NULL) {
        fprintf(stderr, "alias: name or command cannot be NULL\n");
        return;
    }
    new = malloc(sizeof(alias_t));
    if (!new) {
        perror("malloc");
        return;
    }
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->name != NULL && strcmp(tmp->name, name) == 0) {
            free(tmp->cmd);
            tmp->cmd = strdup(cmd);
            free(new);
            return;
        }
    }
    new->name = strdup(name);
    new->cmd = strdup(cmd);
    if (!new->name || !new->cmd) {
        free(new->name);
        free(new->cmd);
        free(new);
        perror("strdup");
        return;
    }
    new->next = *head;
    *head = new;
}

char *get_alias_value(alias_t *head, const char *name)
{
    if (name == NULL)
        return NULL;
    for (; head != NULL; head = head->next) {
        if (head->name != NULL && strcmp(head->name, name) == 0)
            return head->cmd;
    }
    return NULL;
}

void free_aliases(alias_t *head)
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

int my_alias(shell_t *shell)
{
    char *cmd = NULL;

    if (shell == NULL || shell->nb_args < 1 || shell->command == NULL ||
        strcmp(shell->command[0], "alias") != 0)
        return 1;
    if (shell->nb_args == 1)
        return print_alias(shell->aliases, shell);
    else if (shell->nb_args == 2) {
        if (shell->command[1] == NULL) {
            fprintf(stderr, "alias: missing argument\n");
            return 1;
        }
        return print_alias(shell->aliases, shell);
    } else if (shell->nb_args >= 3) {
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
    return 1;
}
