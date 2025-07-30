/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** strip_str
*/

#include "my_sh.h"

char *strip_str(char *str, char remove)
{
    char *copy = malloc(sizeof(char) * (my_strlen(str) + 1));
    int j = 0;

    CHECK_MALLOC(copy, NULL);
    copy[my_strlen(str)] = '\0';
    for (int i = 0; str[i]; i++) {
        if (str[i] == remove)
            continue;
        copy[j] = str[i];
        j++;
    }
    copy[j] = '\0';
    return copy;
}
