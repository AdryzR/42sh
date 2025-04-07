/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_d
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void flag_d(va_list args, int *pntr)
{
    my_put_nbr((int)va_arg(args, int));
}
