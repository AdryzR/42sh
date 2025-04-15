/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_cd
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

static int not_a_dir(shell_t *shell)
{
    my_putstr_ch(2, shell->command[1]);
    my_putstr_ch(2, ": ");
    my_putstr_ch(2, strerror(errno));
    my_putstr_ch(2, ".\n");
    shell->shell_status = 84;
    return 84;
}

static int update_env_line(envi_t *buff, shell_t *shell, char *type,
    char *name)
{
    int size = 0;
    char *new_value = NULL;

    size = my_strlen(type) + my_strlen(name) + 2;
    new_value = malloc(sizeof(char) * (size + 1));
    if (!new_value)
        return 84;
    my_strcpy(new_value, type);
    my_strcat(new_value, "=");
    my_strcat(new_value, name);
    free(buff->env);
    free_array(buff->parts);
    buff->env = my_strdup(new_value);
    buff->parts = my_str_to_word_array(buff->env, "=");
    free(new_value);
    return 0;
}

static int cd_too_many_args(shell_t *shell)
{
    my_putstr_ch(2, "cd: Too many arguments.\n");
    shell->shell_status = 84;
    return 84;
}

static int no_home_dir(shell_t *shell)
{
    my_putstr_ch(2, "cd: No home directory.\n");
    shell->shell_status = 84;
    return 84;
}

static int update_pwd(shell_t *shell, char *old_pwd)
{
    envi_t *buff = shell->envi;

    for (; buff && my_strcmp(buff->parts[0], "OLDPWD") != 0;
        buff = buff->next);
    CHECK_MALLOC(buff, 84);
    update_env_line(buff, shell, "OLPWD", old_pwd);
    for (buff = shell->envi; buff && my_strcmp(buff->parts[0], "PWD") != 0;
        buff = buff->next);
    CHECK_MALLOC(buff, 84);
    update_env_line(buff, shell, "PWD", getcwd(NULL, 0));
    return 0;
}

static int cd_home(shell_t *shell)
{
    envi_t *buff = shell->envi;
    char *old_pwd = getcwd(NULL, 0);
    int status = 0;

    for (; buff && my_strcmp(buff->parts[0], "HOME") != 0;
        buff = buff->next);
    if (!buff) {
        if (shell->home != NULL)
            status = chdir(shell->home);
        else
            return no_home_dir(shell);
    } else
        status = chdir(buff->parts[1]);
    if (status < 0)
        return not_a_dir(shell);
    shell->old_pwd = old_pwd;
    status = update_pwd(shell, old_pwd);
    shell->shell_status = status;
    return status;
}

static int exec_cd(shell_t *shell)
{
    char *old_pwd = getcwd(NULL, 0);
    int status = 0;
    int result = 0;

    result = chdir(shell->command[1]);
    if (result < 0)
        return not_a_dir(shell);
    shell->old_pwd = old_pwd;
    status = update_pwd(shell, old_pwd);
    shell->shell_status = status;
    return status;
}

static int cd_minus(shell_t *shell)
{
    char *old_pwd = getcwd(NULL, 0);
    int status = 0;
    int result = 0;

    result = chdir(shell->old_pwd);
    if (result < 0)
        return not_a_dir(shell);
    shell->old_pwd = old_pwd;
    status = update_pwd(shell, old_pwd);
    shell->shell_status = status;
    return status;
}

int my_cd(shell_t *shell)
{
    if (shell->nb_args > 2)
        return cd_too_many_args(shell);
    if (shell->nb_args == 1)
        return cd_home(shell);
    if (shell->nb_args == 2 && my_strcmp("~", shell->command[1]) == 0)
        return cd_home(shell);
    if (shell->nb_args == 2 && my_strcmp("-", shell->command[1]) == 0)
        return cd_minus(shell);
    return exec_cd(shell);
}
