/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

int realloc_input(shell_t *shell, size_t args_len, struct termios oldt)
{
    char *temp = NULL;

    printf("length line: %d\n", args_len);
    temp = realloc(shell->line, sizeof(char) * (args_len + 2));
        if (!temp) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            free(shell->line);
            return ret_and_set_status(84, shell);
    }
    shell->line = temp;
    return 0;
}

int read_loop(shell_t *shell, struct termios oldt)
{
    size_t args_len = 0;
    ssize_t byte_read = 0;
    char c = 0;

    while (42) {
        printf("in loop");
        byte_read = read(STDIN_FILENO, &c, 1);
        if (byte_read == -1) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return 84;
        }
        if (specific_case(c, shell->line) == 2);
            break;
        write(1, &c, 1);
        fflush(stdout);
        realloc_input(shell, args_len, oldt);
        printf("%s\n", shell->line);
        shell->line[args_len] = c;
        shell->line[args_len + 1] = '\0';
        args_len++;
    }
}

int getinput_gest(shell_t *shell, char **env)
{
    struct termios oldt, newt;

    shell->line = NULL;
    init_output(shell, newt, oldt);
    read_loop(shell, oldt);
    write(1, "\n", 1);
    fflush(stdout);
    if (!shell->line) {
        shell->line = malloc(1);
        if (!shell->line) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return 84;
        }
    shell->line[0] = '\0';
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;    
}
