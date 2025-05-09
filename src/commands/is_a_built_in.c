/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** is_a_built_in
*/

#include <my_sh.h>

/* Liste des builtins */
static const char *builtin_names[] = {
    "exit",
    "setenv",
    "env",
    "unsetenv",
    "cd",
    "which",
    "where",
    "repeat",
    "alias",
    "history",
    "echo",
    NULL
};

/* Liste des fonctions associées aux builtins */
static const builtin_fn_t builtin_fns[] = {
    builtin_exit,
    my_setenv,
    my_env,
    my_unsetenv,
    my_cd,
    my_which,
    my_where,
    my_repeat,
    my_alias,
    exec_print_history,
    my_echo
};

/*
Utilisation d'un argument pour le my_exit en cas de call builtin,
(différent pour CTRL + d, qui utilise aussi my_exit).
*/
int builtin_exit(shell_t *shell)
{
    return my_exit(shell, CURRENT_STATUS);
}

int exec_print_history(shell_t *shell)
{
    (void)shell;
    return print_history();
}

static pid_t fork_builtin(builtin_fn_t builtin, shell_t *shell)
{
    pid_t pid = fork();
    int status;

    if (pid != 0)
        return pid;
    status = builtin(shell);
    exit(status);
}

static int call_builtin(builtin_fn_t builtin, shell_t *shell)
{
    pid_t child_proc;

    if (shell->should_fork_builtin == false)
        return builtin(shell);
    child_proc = fork_builtin(builtin, shell);
    if (child_proc < 0)
        return 84;
    return wait_for_pid(shell, child_proc);
}

/*
Return 1 si l'input pas un builtin, sinon éxecute le builtin et return
ce qu'il return
*/
int is_a_built_in(shell_t *shell, char *command, bool exec)
{
    for (int i = 0; builtin_names[i] != NULL; i++) {
        if (strcmp(command, builtin_names[i]) == 0 && exec == true)
            return call_builtin(builtin_fns[i], shell);
        if (strcmp(command, builtin_names[i]) == 0 && exec == false)
            return 0;
    }
    return NOT_A_BUILTIN;
}
