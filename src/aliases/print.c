/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** print
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
    if (alias == NULL || alias->cmd == NULL) {
        perror("Error: Invalid alias structure\n");
        return 1;
    }
    printf("%s\n", alias->cmd);
    return 0;
}

static int print_all_aliases(const alias_t *list)
{
    if (list == NULL) {
        return print_no_aliases();
    }
    while (list != NULL) {
        if (list->name != NULL && list->cmd != NULL)
            printf("%s\t\t%s\n", list->name, list->cmd);
        list = list->next;
    }
    return 0;
}

static int find_and_print_alias(shell_t *shell, const alias_t *list)
{
    if (shell == NULL || shell->command[1] == NULL)
        return 1;
    while (list != NULL) {
        if (list->name != NULL && strcmp(list->name, shell->command[1]) == 0) {
            return print_single_alias(list);
        }
        list = list->next;
    }
    perror("alias: not found\n");
    return 1;
}

int print_alias(alias_t *list, shell_t *shell)
{
    if (shell == NULL) {
        perror("Error: Invalid shell structure\n");
        return 1;
    }
    if (list == NULL)
        return print_no_aliases();
    switch (shell->nb_args) {
        case 1:
            return print_all_aliases(list);
        case 2:
            return find_and_print_alias(shell, list);
        default:
            perror("Usage: alias [name]\n");
            return 1;
    }
}
