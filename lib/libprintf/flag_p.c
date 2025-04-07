/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_p
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static int my_put_ptr(long nbr, char const *base)
{
    long a;
    int len_str;

    if (nbr == -2147483648)
        return nbr;
    len_str = my_strlen(base);
    a = nbr % len_str;
    nbr = nbr / len_str;
    if (nbr > 0)
        my_put_ptr(nbr, base);
    my_putchar(base[a]);
    return (nbr);
}

void flag_p(va_list args, int *pntr)
{
    long value = va_arg(args, long);

    if (value == 0)
        my_putstr("(nil)");
    else {
        my_putstr("0x");
        my_put_ptr(value, "0123456789abcdef");
    }
}
