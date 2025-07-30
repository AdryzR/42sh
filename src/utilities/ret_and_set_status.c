/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** ret_and_set_status
*/

#include "my_sh.h"

int ret_and_set_status(int ret, shell_t *shell)
{
    shell->shell_status = ret;
    return ret;
}
