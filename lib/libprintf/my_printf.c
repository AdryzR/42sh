/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_printf
*/

#include "../../include/my.h"
#include "../../include/my_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int find_flag(const char *str, int i, va_list args, int *pntr)
{
    char *flag = "cdEeio%suXxfFpn";
    void (*flag_ptr[])(va_list args, int *) = {flag_c, flag_d, flag_e_up,
    flag_e, flag_i, flag_o, flag_prct, flag_s, flag_u, flag_x_up, flag_x,
    flag_f, flag_f_up, flag_p, flag_n};

    for (int j = 0; flag[j] != '\0'; j++) {
        if (str[i + 1] == flag[j]) {
            flag_ptr[j](args, pntr);
            return 1;
        }
    }
    my_putchar(str[i]);
    my_putchar(str[i + 1]);
    return 0;
}

int subflag(const char *str, int i, va_list args, int *pntr)
{
    char temp2[2];
    char *subflag[13] = {"ld", "hd", "li", "hi", "lo", "ho", "lu", "hu",
    "lx", "hx", "lX", "hX", NULL};
    void (*subflag_ptr[])(va_list args, int *) = {flag_ld, flag_hd, flag_li,
    flag_hi, flag_lo, flag_ho, flag_lu, flag_hu, flag_lx, flag_hx, flag_lx_up,
    flag_hx_up};

    temp2[0] = str[i + 1];
    temp2[1] = str[i + 2];
    for (int j = 0; subflag[j] != NULL; j++) {
        if (my_strcmp(temp2, subflag[j]) == 0) {
            subflag_ptr[j](args, pntr);
            return 2;
        }
    }
    return find_flag(str, i, args, pntr);
}

int double_subflag(const char *str, int i, va_list args, int *pntr)
{
    char temp[3];
    char *dbl_subflag[7] = {"lld", "lli", "llo", "llu", "llx", "llX", NULL};
    void (*dbl_subflag_ptr[])(va_list args, int *) = {flag_lld, flag_lli,
    flag_llo, flag_llu, flag_llx, flag_llx_up};

    temp[0] = str[i + 1];
    temp[1] = str[i + 2];
    temp[2] = str[i + 3];
    for (int j = 0; dbl_subflag[j] != NULL; j++) {
        if (my_strcmp(temp, dbl_subflag[j]) == 0) {
            dbl_subflag_ptr[j](args, pntr);
            return 3;
        }
    }
    return subflag(str, i, args, pntr);
}

int start_print(const char *str, va_list args)
{
    int printed_nbr = 0;
    int *number = &printed_nbr;

    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] == '%') {
            i += double_subflag(str, i, args, number);
        } else {
            my_putchar(str[i]);
            printed_nbr++;
        }
    }
}

int my_printf(const char *str, ...)
{
    va_list args;

    va_start(args, str);
    start_print(str, args);
    va_end(args);
}
