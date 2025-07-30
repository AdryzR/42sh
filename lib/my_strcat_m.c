/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_strcat
*/

#include "my.h"
#include <stdlib.h>
#include <unistd.h>

char *my_strcat_m(char *dest, char const *src)
{
    int size = my_strlen(dest) + my_strlen(src) + 1;
    char *new = malloc(sizeof(char) * size);

    if (!new)
        return NULL;
    for (int i = 0; i < my_strlen(dest); i++)
        new[i] = dest[i];
    for (int i = 0; i < my_strlen(src); i++)
        new[i + my_strlen(dest)] = src[i];
    new[size - 1] = '\0';
    return new;
}
