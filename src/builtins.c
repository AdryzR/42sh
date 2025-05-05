/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_a_built_in
*/

#include <my_sh.h>

/*
Utilisation d'un argument pour le my_exit en cas de call builtin,
(différent pour CTRL + d, qui utilise aussi my_exit).
*/
static int builtin_exit(shell_t *shell)
{
    return my_exit(shell, CURRENT_STATUS);
}

/* Liste des builtins */
static const char *builtin_names[] = {
    "exit",
    "setenv",
    "env",
    "unsetenv",
    "cd",
    "alias",
    NULL
};

/* Liste des fonctions associées aux builtins */
static const builtin_fn_t builtin_fns[] = {
    &builtin_exit,
    &my_setenv,
    &my_env,
    &my_unsetenv,
    &my_cd,
    &my_alias
};

/*
Return 1 si l'input pas un builtin, sinon éxecute le builtin et return
ce qu'il return
*/
int is_a_built_in(shell_t *shell)
{
    for (int i = 0; builtin_names[i] != NULL; i++) {
        if (my_strcmp(shell->command[0], builtin_names[i]) == 0) {
            return builtin_fns[i](shell);
        }
    }
    return NOT_A_BUILTIN;
}
