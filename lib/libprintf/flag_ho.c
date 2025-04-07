/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_o
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static short my_octal_nbr(short nb)
{
    if (nb >= 8)
        my_octal_nbr(nb / 8);
    my_putchar((nb % 8) + 48);
}

void flag_ho(va_list args, int *pntr)
{
    my_octal_nbr((int)va_arg(args, int));
}
