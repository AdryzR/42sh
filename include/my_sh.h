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
} shell_t;

int handle_pipes(shell_t *shell);
int exec_pipe(shell_t *shell, char **commands);
void make_right_to_left_red(shell_t *shell, char *filename);
int check_double_r_to_l_errors(shell_t *shell);
int check_r_to_l_errors(shell_t *shell);
bool is_double_ltr_red(shell_t *shell);
bool is_double_rtl_red(shell_t *shell);
int double_left_to_right(shell_t *shell);
void make_left_to_right_red(shell_t *shell, char *filename, bool append);
bool is_ltr_red(shell_t *shell);
bool is_rtl_red(shell_t *shell);
int missing_name_err(char **commands, shell_t *shell);
int check_l_to_r_errors(shell_t *shell);
int ambiguous_redirect_err(char **commands, shell_t *shell, int type);
int check_double_l_to_r_errors(shell_t *shell);
char **str_to_warray(char *str, char *delim);
int left_to_right(shell_t *shell);
char *strip_str(char *str, char remove);
int handle_redirections(shell_t *shell);
int ret_and_set_status(int ret, shell_t *shell);
void add_env_line(char *env, shell_t *shell);
void delete_env_node(envi_t *current, shell_t *shell);
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

#endif
