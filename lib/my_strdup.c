/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_strdup
*/

#include "my.h"

char *my_strdup(const char *str)
{
    char *new = malloc(sizeof(char) * (my_strlen(str) + 1));
    int size = my_strlen(str) + 1;

    if (!new)
        return NULL;
    for (int i = 0; i < size; i++)
        new[i] = '\0';
    my_strcpy(new, str);
    return new;
}
