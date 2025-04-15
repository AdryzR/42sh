/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_str_to_w_array
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

static char **setup_array(char *str, char *delim)
{
    char *copy = my_strdup(str);
    int nb_words = 1;
    int index = 0;
    char **words = NULL;
    char *token = strtok(copy, delim);

    for (; strtok(NULL, delim); nb_words++);
    free(copy);
    copy = my_strdup(str);
    words = malloc(sizeof(char *) * (nb_words + 1));
    CHECK_MALLOC(words, NULL);
    token = strtok(copy, delim);
    while (token != NULL) {
        words[index] = token;
        token = strtok(NULL, delim);
        index++;
    }
    words[nb_words] = NULL;
    free(copy);
    return words;
}

char **my_str_to_warray(char *str, char *delim)
{
    char **new = NULL;

    if (!str || !delim)
        return NULL;
    new = setup_array(str, delim);
    if (!new)
        return NULL;
    return new;
}
