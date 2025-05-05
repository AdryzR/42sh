/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** check_command
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

static void clean_path(shell_t *shell, char *dir)
{
    shell->full_path[0] = '\0';
    my_strcat(shell->full_path, dir);
    my_strcat(shell->full_path, "/");
    my_strcat(shell->full_path, shell->command[0]);
}

static int command_not_found(shell_t *shell)
{
    my_putstr_ch(2, shell->command[0]);
    my_putstr_ch(2, ": Command not found.\n");
    shell->shell_status = 84;
    return 84;
}

static int exisiting_path(shell_t *shell, char *copy)
{
    free(copy);
    return 0;
}

static int return_error(char *copy)
{
    free(copy);
    return 84;
}

int loop_on_paths(shell_t *shell)
{
    char *dir = NULL;
    int path_size = 0;
    struct stat file_stat;
    char *copy = NULL;

    CHECK_MALLOC(shell->path_copy, command_not_found(shell));
    copy = my_strdup(shell->path_copy);
    dir = strtok(copy, ":");
    while (dir) {
        path_size = my_strlen(dir) + my_strlen(shell->command[0]) + 2;
        free(shell->full_path);
        shell->full_path = malloc(sizeof(char) * path_size);
        CHECK_MALLOC(shell->full_path, return_error(copy));
        clean_path(shell, dir);
        if (stat(shell->full_path, &file_stat) == 0 &&
            (file_stat.st_mode & S_IXUSR))
            return exisiting_path(shell, copy);
        dir = strtok(NULL, ":");
    }
    return return_error(copy);
}

static void set_default_path(shell_t *shell)
{
    char *path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:"
    "/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin";

    shell->path_copy = strdup(path);
}

int check_commands(shell_t *shell)
{
    char *dir = NULL;
    int status = 0;

    for (int i = 0; shell->command[0][i]; i++)
        if (shell->command[0][i] == '/') {
            shell->full_path = my_strdup(shell->command[0]);
            return 0;
        }
    if (!shell->path_copy)
        set_default_path(shell);
    status = loop_on_paths(shell);
    if (status == 84)
        return command_not_found(shell);
}
