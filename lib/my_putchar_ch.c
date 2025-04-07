/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** my_putchar_ch
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void my_putchar_ch(char c, int fd)
{
    write(fd, &c, 1);
}
