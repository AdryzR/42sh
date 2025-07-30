/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** execute_sudo
*/

#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

static int check_signal_status(int status)
{
    switch (WTERMSIG(status)) {
    case SIGSEGV:
        fprintf(stderr, "Segmentation fault");
        break;
    case SIGFPE:
        fprintf(stderr, "Floating exception");
        break;
    default:
        break;
    }
    if (WCOREDUMP(status))
        fprintf(stderr, " (core dumped)");
    fprintf(stderr, "\n");
    return status;
}

int wait_for_pid(shell_t *shell, int c_pid)
{
    int status = 0;

    if (!shell->should_skip_wait)
        waitpid(c_pid, &status, 0);
    shell->shell_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        shell->shell_status = check_signal_status(status);
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
    int err = errno;

    fprintf(stderr, "%s", shell->command[0]);
    fprintf(stderr, ": ");
    if (err == ENOENT) {
        fprintf(stderr, "Command not found.\n");
        return;
    }
    if (!is_executable(shell->full_path)) {
        fprintf(stderr, "Permission denied.\n");
        return;
    }
    if (err == ENOEXEC) {
        fprintf(stderr, "%s", strerror(err));
        fprintf(stderr, ". Binary file not executable.\n");
        return;
    }
    fprintf(stderr, "%s", strerror(err));
    fprintf(stderr, ".\n");
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
        exit(1);
    }
    free_array(env);
    return 0;
}
