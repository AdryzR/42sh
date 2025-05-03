/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_setenv
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

int too_many_args(shell_t *shell)
{
    shell->shell_status = 84;
    my_putstr_ch(2, "setenv: Too many arguments.\n");
    return 84;
}

int check_args_len(shell_t *shell)
{
    if (shell->nb_args == 1) {
        my_env(shell);
        shell->shell_status = 0;
        return 1;
    }
    if (shell->nb_args > 3)
        return too_many_args(shell);
    return 0;
}

int new_env_line(envi_t *buff, shell_t *shell)
{
    char *new_line = NULL;
    int size = 0;

    if (shell->nb_args == 3)
        size = my_strlen(shell->command[1]) + my_strlen(shell->command[2]) + 2;
    else if (shell->nb_args == 2)
        size = my_strlen(shell->command[1]) + 2;
    new_line = malloc(sizeof(char) * (size + 2));
    CHECK_MALLOC(new_line, 84);
    my_strcpy(new_line, shell->command[1]);
    my_strcat(new_line, "=");
    if (shell->nb_args == 3)
        my_strcat(new_line, shell->command[2]);
    add_env_line(new_line, shell);
    free(new_line);
    return 0;
}

static void free_to_replace_env(envi_t *buff)
{
    free(buff->env);
    for (int i = 0; buff->parts[i]; i++)
        free(buff->parts[i]);
    free(buff->parts);
}

int replace_env_line(envi_t *buff, shell_t *shell)
{
    int size = 0;
    char *new_value = NULL;

    if (shell->nb_args == 3)
        size = my_strlen(shell->command[1]) + my_strlen(shell->command[2]) + 2;
    else if (shell->nb_args == 2)
        size = my_strlen(shell->command[1] + 1);
    new_value = malloc(sizeof(char) * (size + 1));
    if (!new_value)
        return 84;
    my_strcpy(new_value, shell->command[1]);
    my_strcat(new_value, "=");
    if (shell->nb_args == 3)
        my_strcat(new_value, shell->command[2]);
    buff->env = my_strdup(new_value);
    buff->parts = my_str_to_word_array(buff->env, "=");
    free(new_value);
    return 0;
}

static bool is_char_allowed(char c)
{
    return
        (c == '_') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static bool is_alphanumeric(char c)
{
    return
        (c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z');
}

static int check_env_arg(shell_t *shell)
{
    if (is_char_allowed(shell->command[1][0]) == false) {
        my_putstr_ch(2, "setenv: Variable name must begin with a letter.\n");
        shell->shell_status = 84;
        return 84;
    }
    for (int i = 1; shell->command[1][i]; i++)
        if (is_alphanumeric(shell->command[1][i]) == false) {
            my_putstr_ch(2, "setenv: Variable name must contain alphanumeric "
                "characters.\n");
            shell->shell_status = 84;
            return 84;
        }
    return 0;
}

int my_setenv(shell_t *shell)
{
    int ret = check_args_len(shell);
    envi_t *buff = shell->envi;

    if (ret == 84)
        return 84;
    if (ret == 1)
        return 0;
    if (check_env_arg(shell) == 84)
        return 84;
    for (; buff && my_strcmp(buff->parts[0], shell->command[1]) != 0;
        buff = buff->next);
    if (!buff)
        return new_env_line(buff, shell);
    return replace_env_line(buff, shell);
}

/* setenv	- Nom de variable contenant = ou des caractères invalides (-, .)
- Nom commençant par un chiffre
- Valeur non entourée de guillemets si elle contient des espaces
- Plus de deux arguments
unsetenv	- Plus d'un argument
- Nom de variable invalide*/
