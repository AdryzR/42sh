/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_x
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void flag_x(va_list args, int *pntr)
{
    my_put_nbr_base((int)va_arg(args, int), "0123456789abcdef");
}
