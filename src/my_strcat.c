/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_strcat
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_printf.h"
#include "my_sh.h"

char *my_strcat(char *dest, char const *src)
{
    int d_len = my_strlen(dest);
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[d_len + i] = src[i];
    dest[d_len + i] = '\0';
    return dest;
}
