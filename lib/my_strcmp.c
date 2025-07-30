/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_strcmp
*/

#include <unistd.h>
#include <stdlib.h>

int my_strcmp(char const *s1, char const *s2)
{
    return (*s1 && *s2 && *s1 == *s2) ? my_strcmp(s1 + 1, s2 + 1) : *s1 - *s2;
}
