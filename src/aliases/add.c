/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** add
*/

#include "my.h"
#include "my_sh.h"

alias_t *find_alias(alias_t *head, const char *name)
{
    alias_t *tmp = head;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->name != NULL && strcmp(tmp->name, name) == 0) {
            return tmp;
        }
    }
    return NULL;
}

void prepend_alias_to_list(alias_t **head, alias_t *node)
{
    node->next = *head;
    *head = node;
}

int init_alias_node(alias_t *node, const char *name, const char *cmd)
{
    node->name = strdup(name);
    node->cmd = strdup(cmd);
    if (!node->name || !node->cmd) {
        free(node->name);
        free(node->cmd);
        perror("strdup");
        return 0;
    }
    return 1;
}

void add_alias(alias_t **head, const char *name, const char *cmd)
{
    alias_t *existing;
    alias_t *new;

    if (name == NULL || cmd == NULL)
        return;
    existing = find_alias(*head, name);
    if (existing != NULL) {
        free(existing->cmd);
        existing->cmd = strdup(cmd);
        return;
    }
    new = malloc(sizeof(alias_t));
    init_alias_node(new, name, cmd);
    prepend_alias_to_list(head, new);
}
