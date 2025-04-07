/*
** EPITECH PROJECT, 2024
** Workshop_LinkedList
** File description:
** my_strcpuf
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

char *my_strcpy(char *dest, const char *src)
{
    size_t i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
