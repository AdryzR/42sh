/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_printf
*/

#ifndef MY_H

    #define MY_H
    #include <stdbool.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include "my_printf.h"

    #define CHECK_MALLOC(ptr, retval) if (ptr == NULL) return retval

char *my_strcpy(char *dest, const char *src);
char *my_strdup(const char *str);
int len_array(char **array);
void my_putchar(char c);
void my_putchar_ch(char c, int fd);
int my_strcmp(char const *s1, char const *s2);
char *my_strncpy(char const *src, int n);
void my_putchar_ch(char c, int fd);
int my_put_nbr(int nb);
int my_put_nbr_ch(int nb, int fd);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);

#endif
