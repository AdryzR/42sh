/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** word_array_to_str_for_repeat.c
*/

#include "my_sh.h"

static int calculate_len(char **tab, char *delim, int start)
{
    int len = 0;

    for (int i = start; tab[i]; ++i) {
        if (tab[i + 1])
            len += strlen(delim);
        for (int k = 0; tab[i][k]; ++k)
            ++len;
    }
    return len;
}

static char *add_delim(char **tab, char *buff, char *delim, int *count)
{
    for (int i = 0; delim[i]; ++i) {
        buff[(*count)] = delim[i];
        (*count) += 1;
    }
    return buff;
}

char *word_array_to_str(char **tab, char *delim, int start)
{
    int len = calculate_len(tab, delim, start);
    char *buff = malloc(sizeof(char) * (len + 2));
    int count = 0;

    if (!buff)
        return NULL;
    for (int i = start; tab[i]; ++i) {
        for (int k = 0; tab[i][k]; ++k) {
            buff[count] = tab[i][k];
            ++count;
        }
        if (tab[i + 1])
            buff = add_delim(tab, buff, delim, &count);
    }
    buff[len] = '\n';
    buff[len + 1] = '\0';
    return buff;
}
