/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_getenv
*/

#include "my.h"

char *my_getenv(char **env, char *tofind)
{
    char **env_line;

    for (int i = 0; env[i]; i++) {
        env_line = my_str_to_word_array(env[i], " =");
        if (my_strcmp(env_line[0], tofind) == 0)
            return env_line[1];
    }
}
