/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** print_prompt
*/

#include <my_sh.h>

void print_prompt(shell_t *shell)
{
    char path[SH_PATH_MAX];
    char *user = my_getenv(shell, "USER");

    if (user != NULL)
        printf("\033[0;32m@%s", user);
    if (!user)
        printf("\033[0;32m@%s", getlogin());
    if (getcwd(path, SH_PATH_MAX) != NULL)
        printf("\033[0;36m>%s", path);
    printf("> \033[0m");
    fflush(stdout);
}
