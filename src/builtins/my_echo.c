/*
** EPITECH PROJECT, 2024
** B-PSU-200-STG-2-1-42sh-adrien.raphanaud
** File description:
** my_echo.c
*/

#include "my_sh.h"

int my_echo(shell_t *shell)
{
    bool n = 0;
    int start = 1;

    if (strcmp(shell->command[1], "-n") == 0) {
        n = true;
        start = 2;
    }
    for (int i = start; shell->command[i]; ++i) {
        printf("%s", shell->command[i]);
        if (shell->command[i + 1])
            printf(" ");
    }
    if (n == false)
        printf("\n");
    shell->shell_status = 0;
    return 0;
}
