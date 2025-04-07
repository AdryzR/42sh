/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** my_putchar
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb <= 9)
        my_putchar(nb + 48);
    else {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    }
    return (0);
}
