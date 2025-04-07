/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** str_to_warray
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "my_sh.h"

static void free_my_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

bool is_delim(const char *str, const char *delim)
{
    return my_strncmp(str, delim, my_strlen(delim)) == 0;
}

int number_of_words(char *str, char *delim)
{
    int nb_words = 0;
    size_t delim_len = my_strlen(delim);

    for (bool is_word = false; *str; str++) {
        if (is_delim(str, delim)) {
            is_word = false;
            str += delim_len - 1;
            continue;
        }
        if (!is_word) {
            is_word = true;
            nb_words++;
        }
    }
    return nb_words;
}

int size_of_word(char *word, char *delim)
{
    int length = 0;
    size_t delim_len = my_strlen(delim);

    while (word[length] && !is_delim(word + length, delim))
        ++length;
    return length;
}

int set_words(char **words, char *str, char *delim)
{
    int pos_words = 0;
    int word_len = 0;
    size_t delim_len = my_strlen(delim);

    while (*str) {
        while (is_delim(str, delim) && *str)
            str += delim_len;
        if (!*str)
            break;
        word_len = size_of_word(str, delim);
        words[pos_words] = malloc(sizeof(char) * (word_len + 1));
        if (!words[pos_words])
            return 84;
        words[pos_words] = my_strncpy(str, word_len);
        words[pos_words][word_len] = '\0';
        str += word_len;
        pos_words++;
    }
    words[pos_words] = NULL;
    return 0;
}

char **str_to_warray(char *str, char *delim)
{
    char **words = NULL;
    int words_count = 0;
    int is_error = 0;

    if (!str || !delim)
        return NULL;
    words_count = number_of_words(str, delim);
    words = malloc(sizeof(char *) * (words_count + 1));
    if (!words)
        return NULL;
    for (size_t i = 0; i < words_count + 1; i++)
        words[i] = NULL;
    is_error = set_words(words, str, delim);
    if (is_error == 84) {
        free_my_array(words);
        return NULL;
    }
    return words;
}
