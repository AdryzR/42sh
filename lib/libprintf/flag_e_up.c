/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** flag_e_up
*/

#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static void print_exposent(int exposent)
{
    if (exposent < 10) {
        my_putchar('0');
        my_put_nbr(exposent);
    } else if (exposent > 10) {
        my_put_nbr(exposent);
    }
}

static void positive(double myfloat)
{
    int exposent = 0;

    while (myfloat > 10) {
        myfloat /= 10;
        exposent++;
    }
    my_printf("%f", myfloat);
    my_putstr("E+");
    print_exposent(exposent);
}

static void negative(double myfloat)
{
    int exposent = 0;

    myfloat = -myfloat;
    while (myfloat > 10) {
        myfloat /= 10;
        exposent++;
    }
    my_printf("-%f", myfloat);
    my_putstr("E+");
    print_exposent(exposent);
}

static void positive_zero(double myfloat)
{
    int exposent = 0;

    while (myfloat < 1) {
        myfloat *= 10;
        exposent++;
    }
    my_printf("%f", myfloat);
    my_putstr("E-");
    print_exposent(exposent);
}

static void negative_zero(double myfloat)
{
    int exposent = 0;

    myfloat = -myfloat;
    while (myfloat < 1) {
        myfloat *= 10;
        exposent++;
    }
    my_printf("-%f", myfloat);
    my_putstr("E-");
    print_exposent(exposent);
}

static void catch_zero(double myfloat)
{
    if (myfloat >= 0) {
        positive_zero(myfloat);
    } else if (myfloat <= 0) {
        negative_zero(myfloat);
    }
}

void flag_e_up(va_list args, int *pntr)
{
    double myfloat = va_arg(args, double);

    if (myfloat >= 1) {
        positive(myfloat);
        return;
    }
    if (myfloat <= -1) {
        negative(myfloat);
        return;
    }
    if (-1 <= myfloat <= 1) {
        catch_zero(myfloat);
        return;
    }
}
