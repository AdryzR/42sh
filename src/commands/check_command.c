/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** check_command
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include <fcntl.h>
#include "printf.h"
#include "my_sh.h"

static void clean_path(shell_t *shell, char *dir, char *command)
{
    shell->full_path[0] = '\0';
    my_strcat(shell->full_path, dir);
    my_strcat(shell->full_path, "/");
    my_strcat(shell->full_path, command);
}

static int command_not_found(shell_t *shell, char *command, bool print)
{
    if (print == true) {
        my_putstr_ch(2, command);
        my_putstr_ch(2, ": Command not found.\n");
    }
    shell->shell_status = 1;
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

int loop_on_paths(shell_t *shell, char *command, bool print)
{
    char *dir = NULL;
    int path_size = 0;
    struct stat file_stat;
    char *copy = NULL;

    CHECK_MALLOC(shell->path_copy, command_not_found(shell, command, print));
    copy = my_strdup(shell->path_copy);
    dir = strtok(copy, ":");
    while (dir) {
        path_size = my_strlen(dir) + my_strlen(command) + 2;
        free(shell->full_path);
        shell->full_path = malloc(sizeof(char) * path_size);
        CHECK_MALLOC(shell->full_path, return_error(copy));
        clean_path(shell, dir, command);
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

    if (shell->path_copy)
        free(shell->path_copy);
    shell->path_copy = strdup(path);
}

int check_commands(shell_t *shell, char *command, bool print)
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
    status = loop_on_paths(shell, command, print);
    if (status == 84)
        return command_not_found(shell, command, print);
    return 0;
}
