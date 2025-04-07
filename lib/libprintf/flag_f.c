/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_f
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static void verify_zero(double myfloat)
{
    if (myfloat < 0.01)
        my_putchar('0');
    if (myfloat < 0.001)
        my_putchar('0');
    if (myfloat < 0.0001)
        my_putchar('0');
    if (myfloat < 0.00001)
        my_putchar('0');
    if (myfloat < 0.000001)
        my_putchar('0');
}

static void print_float(double myfloat)
{
    signed long int intpart;
    signed long int decpart;

    intpart = (signed long int)myfloat;
    my_put_nbr(intpart);
    my_putchar('.');
    myfloat -= intpart;
    verify_zero(myfloat);
    myfloat *= 1000000;
    decpart = (signed long int)(myfloat + 0.5);
    my_put_nbr(decpart);
}

void flag_f(va_list args, int *pntr)
{
    double myfloat;

    myfloat = va_arg(args, double);
    if (myfloat < 0) {
        myfloat = -myfloat;
        my_putchar('-');
    }
    print_float(myfloat);
}
