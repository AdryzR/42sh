/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_hi
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static short my_put_short(short nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb <= 9)
        my_putchar(nb + 48);
    else {
        my_put_short(nb / 10);
        my_put_short(nb % 10);
    }
    return (0);
}

void flag_hi(va_list args, int *pntr)
{
    my_put_short((int)va_arg(args, int));
}
