/*
** EPITECH PROJECT, 2024
** printf
** File description:
** printf
*/

#ifndef MY_H

    #define MY_H
    #define CHECK_MALLOC(ptr, retval) if (ptr == NULL) return retval
    #include <stdbool.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
char *my_strcpy(char *dest, const char *src);
char *my_strdup(const char *str);
char **my_str_to_word_array(char *str, char *delim);
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
