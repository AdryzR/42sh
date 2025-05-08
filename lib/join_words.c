/*
** EPITECH PROJECT, 2025
** builtin
** File description:
** join_words
*/

#include <stdlib.h>
#include <string.h>
#include <my_sh.h>

char *join_words(char **words)
{
    size_t total_len = 0;
    int count = 0;
    char *result = NULL;

    CHECK_MALLOC(words, NULL);
    for (int i = 0; words[i]; ++i) {
        total_len += strlen(words[i]);
        ++count;
    }
    if (count > 1)
        total_len += (count - 1);
    result = malloc(total_len + 1);
    CHECK_MALLOC(result, NULL);
    result[0] = '\0';
    for (int i = 0; words[i]; ++i) {
        strcat(result, words[i]);
        if (words[i + 1])
            strcat(result, " ");
    }
    return result;
}
