/*
** EPITECH PROJECT, 2025
** B-CPE-110-STG-1-1-secured-mateo.antoni-christ
** File description:
** secured
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_sh.h"
#include <lexer.h>
#include <parser.h>
#include <interpreter.h>

int main(int ac, char **av, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    init_struct(shell, env);
    main_loop(shell);
    return 0;
}
