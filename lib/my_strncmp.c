/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_strncmp
*/

#include "my.h"

int my_strncmp(char const *s1, char const *s2, int size)
{
    for (int i = 0; i < size && (s1[i] != '\0' && s2[i] != '\0'); i++) {
        if (s1[i] != s2[i])
            return (unsigned char)s1[i] - (unsigned char)s2[i];
    }
    return 0;
}
