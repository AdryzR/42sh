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

int my_put_nbr_ch(int nb, int fd)
{
    if (nb < 0) {
        my_putchar_ch('-', fd);
        nb = -nb;
    }
    if (nb <= 9)
        my_putchar_ch(nb + 48, fd);
    else {
        my_put_nbr_ch(nb / 10, fd);
        my_put_nbr_ch(nb % 10, fd);
    }
    return (0);
}
