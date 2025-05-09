/*
** EPITECH PROJECT, 2024
** B-PSU-200-STG-2-1-42sh-adrien.raphanaud
** File description:
** my_echo.c
*/

#include "my_sh.h"

int my_echo(shell_t *shell)
{
    for (int i = 1; shell->command[i]; ++i) {
        printf("%s", shell->command[i]);
        if (shell->command[i + 1])
            printf(" ");
    }
    printf("\n");
    return 0;
}
