/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_u
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static int my_put_unsigned_nbr(unsigned int nb)
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

void flag_u(va_list args, int *pntr)
{
    if (0 <= args <= 4294967295) {
        my_put_unsigned_nbr((unsigned int)va_arg(args, unsigned int));
    }
}
