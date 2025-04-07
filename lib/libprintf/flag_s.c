/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_s
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void flag_s(va_list args, int *pntr)
{
    my_putstr((char *)va_arg(args, char *));
}
