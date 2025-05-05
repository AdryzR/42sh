/*
** EPITECH PROJECT, 2025
** Sudo
** File description:
** execute_sudo
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

// TODO: Implement print for SIGFPE
static void check_signal_status(int status)
{
    if (WTERMSIG(status) != SIGSEGV)
        return;
    if (WCOREDUMP(status))
        printf("Segmentation fault (core dumped)\n");
    else
        printf("Segmentation fault\n");
}

int wait_for_pid(shell_t *shell, int c_pid)
{
    int status = 0;

    if (!shell->should_skip_wait)
        waitpid(c_pid, &status, 0);
    shell->shell_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        check_signal_status(status);
        shell->shell_status = 84;
    }
    return 0;
}

char **env_ll_to_array(shell_t *shell)
{
    envi_t *buff = shell->envi;
    int ll_len = 0;
    char **envi = NULL;
    int idx = 0;

    for (; buff; buff = buff->next)
        ll_len++;
    envi = malloc(sizeof(char *) * (ll_len + 1));
    if (!envi)
        return NULL;
    for (buff = shell->envi; buff; buff = buff->next) {
        envi[idx] = my_strdup(buff->env);
        idx++;
    }
    envi[idx] = NULL;
    return envi;
}

static bool is_executable(const char *filename)
{
    struct stat st;

    return (stat(filename, &st) == 0 && (st.st_mode & S_IXUSR));
}

void my_perror(shell_t *shell)
{
    struct stat st;

    my_putstr_ch(2, shell->command[0]);
    my_putstr_ch(2, ": ");
    if (!is_executable(shell->line)) {
        my_putstr_ch(2, "Command not found.\n");
        return;
    }
    my_putstr_ch(2, strerror(errno));
    if (errno == ENOEXEC)
        my_putstr_ch(2, ". Binary file not executable");
    my_putstr_ch(2, ".\n");
}

int execute_cmd(shell_t *shell)
{
    char **env = env_ll_to_array(shell);
    int p_pid = getpid();
    int c_pid = -1;
    int nb_args = 0;

    c_pid = fork();
    if (c_pid == -1)
        return 84;
    if (c_pid != 0)
        wait_for_pid(shell, c_pid);
    else {
        execve(shell->full_path, shell->command, env);
        my_perror(shell);
        exit(84);
    }
    free_array(env);
    return 0;
}
