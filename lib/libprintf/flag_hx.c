/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_hx
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static int my_put_nbr_base_x(short int nbr, char const *base)
{
    int a;
    int len_str;

    if (nbr == -2147483648)
        return nbr;
    len_str = my_strlen(base);
    a = nbr % len_str;
    nbr = nbr / len_str;
    if (nbr > 0)
        my_put_nbr_base(nbr, base);
    my_putchar(base[a]);
    return (nbr);
}

void flag_hx(va_list args, int *pntr)
{
    my_put_nbr_base((int)va_arg(args, int), "0123456789abcdef");
}
