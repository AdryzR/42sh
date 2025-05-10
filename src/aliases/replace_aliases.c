/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** replace_aliases
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "my_sh.h"

const char *find_best_alias(const char *word, alias_t *curr)
{
    const char *replacement = NULL;
    size_t max_len = 0;
    size_t len = 0;

    for (; curr; curr = curr->next) {
        if (strcmp(word, curr->name) != 0)
            continue;
        len = strlen(curr->name);
        if (len > max_len) {
            max_len = len;
            replacement = curr->cmd;
        }
    }
    return replacement;
}

bool expand_single_word_alias(shell_t *shell, char **word, alias_t *head)
{
    const char *replacement = NULL;
    int count = 0;

    while (1) {
        replacement = find_best_alias(*word, head);
        if (replacement == NULL)
            return true;
        if (strcmp(replacement, *word) == 0)
            return true;
        free(*word);
        *word = strdup(replacement);
        ++count;
        if (count == ALIAS_LOOP) {
            shell->shell_status = 1;
            fprintf(stderr, "Alias loop.\n");
            return false;
        }
    }
}

bool expand_aliases(shell_t *shell, char **words, alias_t *head)
{
    for (size_t i = 0; words[i]; ++i) {
        if (!expand_single_word_alias(shell, &words[i], head))
            return false;
    }
    return true;
}

char *replace_aliases(shell_t *shell, char *input, alias_t *aliases)
{
    char **words = my_str_to_word_array(input, " \t\n");
    char *final = NULL;

    CHECK_MALLOC(words, input);
    if (expand_aliases(shell, words, aliases))
        final = join_words(words);
    free_array(words);
    return final;
}
