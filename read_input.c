/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

int read_loop(shell_t *shell, struct termios oldt)
{
    size_t args_len = 0;
    ssize_t byte_read = 0;
    char c = 0;

    shell->line = malloc(sizeof(char) * 1024);
    byte_read = read(STDIN_FILENO, &c, 1);
    while (byte_read > 0 && c != '\n') {
        specific_case(c, shell->line);
        shell->line[args_len] = c;
        shell->line[args_len + 1] = '\0';
        args_len++;
        byte_read = read(STDIN_FILENO, &c, 1);
    }
    if (byte_read == 0)
        exit(84);
    if (c == 10)
        return 0;
}

int getinput_gest(shell_t *shell, char **env)
{
    struct termios oldt, newt;

    shell->line = NULL;
    init_output(shell, newt, oldt);
    read_loop(shell, oldt);
    fflush(stdout);
    if (!shell->line) {
        shell->line = malloc(sizeof(char));
        if (!shell->line) {
            return 84;
        }
    shell->line[0] = '\0';
    }
    return 0;    
}
