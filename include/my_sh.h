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
    #define STDIN STDIN_FILENO
    #define STDOUT STDOUT_FILENO
    #define MAX_LINES 100
    #define ALIAS_LOOP 10000
    #define LS_COLOR "ls --color"
    #define NOT_A_BUILTIN 1

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
    #include <errno.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdarg.h>
    #include <stddef.h>
    #include <signal.h>
    #include <parser.h>

typedef enum error_e {
    FAILURE = 84,
    EMPTY_LINE = 42
} error_t;

typedef struct alias_s {
    char *name;
    char *cmd;
    struct alias_s *next;
} alias_t;

typedef struct envi_s {
    char *env;
    char **parts;
    struct envi_s *prev;
    struct envi_s *next;
} envi_t;

typedef struct history_s {
    int index;
    int tmp_index;
    int last_return;
} history_t;

typedef struct alloc_s {
    int nb_char;
    int nb_alloc;
} alloc_t;

typedef struct shell_s {
    int nb_args;
    envi_t *envi;
    int shell_status;
    size_t args_len;
    size_t cursor_pos;
    char *line;
    char **command;
    char *path_copy;
    char *full_path;
    char *home;
    char *old_pwd;
    int nb_pipes;
    int nb_parths;
    bool should_skip_wait;
    history_t *history;
    bool should_fork_builtin;
    int saved_fds[2];
    alias_t *aliases;
    alloc_t *alloc;
    char *input;
} shell_t;

typedef int (*builtin_fn_t)(shell_t *shell);
int builtin_exit(shell_t *shell);

int make_redirect_out(shell_t *shell, char *filename, redir_type_t type);
int make_redirect_in(shell_t *shell, char *filename);
int make_redir_heredoc(shell_t *shell, const char *eof);

void main_loop(shell_t *shell, ssize_t bytes_read);

glob_t globbing(char *pattern);

void setup_path_copy(shell_t *shell);
int wait_for_pid(shell_t *shell, int c_pid);
int is_a_built_in(shell_t *shell, char *command, bool exec);
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
int check_commands(shell_t *shell, char *command, bool print);
int my_exit(shell_t *shell, int exit_status);
int execute_cmd(shell_t *box);
int my_putstr_ch(int fd, char const *str);
int my_echo(shell_t *shell);

char *read_line(shell_t *shell);
char *arrows_key(shell_t *shell, history_t *hist, char c, char *line);

// History
int history_gest(shell_t *shell, history_t *hist);
int init_output(struct termios *newt, struct termios *oldt);
void set_index(shell_t *shell, history_t *hist);
int print_history(void);
int exec_print_history(shell_t *shell);

void print_prompt(shell_t *shell);
int my_which(shell_t *shell);
int my_where(shell_t *shell);
lexer_t update_lexer(lexer_t lexer, char *line);
int my_repeat(shell_t *shell);
char *word_array_to_str(char **tab, char *delim, int start);

// alias
int my_alias(shell_t *shell);
char *replace_aliases(shell_t *shell, char *input, alias_t *aliases);
alias_t *find_alias(alias_t *head, const char *name);
void prepend_alias_to_list(alias_t **head, alias_t *node);
int init_alias_node(alias_t *node, const char *name, const char *cmd);
void add_alias(alias_t **head, const char *name, const char *cmd);
static int print_no_aliases(void);
static int print_single_alias(const alias_t *alias);
static int print_all_aliases(const alias_t *list);
static int find_and_print_alias(shell_t *shell, const alias_t *list);
int print_alias(alias_t *list, shell_t *shell);

#endif
