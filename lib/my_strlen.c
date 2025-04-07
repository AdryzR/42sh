/*
** EPITECH PROJECT, 2024
** my_strlen.c
** File description:
** my_strlen
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int my_strlen(char const *str)
{
    int char_count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        char_count++;
    }
    return char_count;
}
