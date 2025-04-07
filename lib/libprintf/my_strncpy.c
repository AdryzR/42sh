/*
** EPITECH PROJECT, 2024
** B-CPE-101-STG-1-1-myprintf-malo.brunetti
** File description:
** my_strncpy
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

char *my_strncpy(char const *src, int n)
{
    int i = 0;
    char *dest = malloc(n + 1);

    if (!dest)
        return NULL;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    dest[n] = '\0';
    return dest;
}
