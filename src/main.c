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

void print_prompt2(char **env)
{
    char *user = my_getenv(env, "USER");
    char cwd[1000];

    user = my_strcat(user, "@");
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        write(1, "\033[0;32m", my_strlen("\033[0;32m"));
        write(1, user, my_strlen(user));
        write(1, "\033[0;36m", my_strlen("\033[0;36m"));
        write(1, cwd, my_strlen(cwd));
        write(1, "> ", 2);
        write(1, "\033[0m", my_strlen("\033[0m"));
    }
}



int main(int ac, char **av, char **env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (!shell)
        return 84;
    init_struct(shell, env);
    main_loop(shell);
    return 0;
}
