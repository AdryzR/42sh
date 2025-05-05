/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** my_sh
*/

#ifndef MY_SH_H_
    #define MY_SH_H_
    #define INPUT 0
    #define OUTPUT 1
    #define MY_SH
    #define NOT_A_BUILTIN 1
    #define SH_PATH_MAX 4096
    #define CHECK_MALLOC(ptr, retval) if (ptr == NULL) return retval
    #define CURRENT_STATUS 150000
    #define ATTRIB(ptr) free_array(ptr) ENDL
    #define OPTI_RET(ptr, retval) ATTRIB(ptr) return retval
    #define STDIN STDIN_FILENO
    #define STDOUT STDOUT_FILENO
    #include "my.h"
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <parser.h>

typedef enum error_e {
    FAILURE = 84,
    EMPTY_LINE = 42
} error_t;

typedef struct envi_s {
    char *env;
    char **parts;
    struct envi_s *prev;
    struct envi_s *next;
} envi_t;

typedef struct shell_s {
    int nb_args;
    envi_t *envi;
    int shell_status;
    char *line;
    char **command;
    char *path_copy;
    char *full_path;
    char *home;
    char *old_pwd;
    int nb_pipes;
    int nb_parths;
    bool should_skip_wait;
    bool should_fork_builtin;
    int saved_fds[2];
    ast_t *program;
} shell_t;

typedef int (*builtin_fn_t)(shell_t *shell);
int builtin_exit(shell_t *shell);

int make_redirect_out(shell_t *shell, char *filename, redir_type_t type);
int make_redirect_in(shell_t *shell, char *filename);
int make_redir_heredoc(shell_t *shell, char *eof);

void main_loop(shell_t *shell);

int wait_for_pid(shell_t *shell, int c_pid);
int is_a_built_in(shell_t *shell);
int missing_name_err(char **commands, shell_t *shell);
char **str_to_warray(char *str, char *delim);
int left_to_right(shell_t *shell);
char *strip_str(char *str, char remove);
int handle_redirections(shell_t *shell);
int ret_and_set_status(int ret, shell_t *shell);
char *my_getenv(shell_t *shell, char *tofind);
void add_env_line(char *env, shell_t *shell);
void delete_env_node(envi_t *current, shell_t *shell);
char *my_getcwd(void);
int my_cd(shell_t *shell);
void init_struct(shell_t *shell, char **env);
void free_array(char **array);
char *my_strcat(char *dest, char const *src);
char *my_strcat_m(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int size);
int my_unsetenv(shell_t *shell);
int my_env(shell_t *shell);
int new_env_line(envi_t *buff, shell_t *shell);
int check_shell_args(shell_t *shell);
int my_setenv(shell_t *shell);
void free_all(shell_t *shell);
int check_commands(shell_t *shell);
int my_exit(shell_t *shell, int exit_status);
int execute_cmd(shell_t *box);
int my_putstr_ch(int fd, char const *str);
void print_prompt(shell_t *shell);

#endif
