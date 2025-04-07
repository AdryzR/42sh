/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_li
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static void my_put_long(long int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb <= 9)
        my_putchar(nb + 48);
    else {
        my_put_long(nb / 10);
        my_put_long(nb % 10);
    }
    return;
}

void flag_li(va_list args, int *pntr)
{
    my_put_long((long int)va_arg(args, long int));
}
