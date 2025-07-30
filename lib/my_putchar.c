/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_putchar
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
