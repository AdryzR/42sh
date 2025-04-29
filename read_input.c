/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

static int error_case(char c, ssize_t byte_read)
{
    if (c == 4)
        exit(0);
    if (byte_read <= 0)
        return 84;
    return 0;
}

int read_loop(shell_t *shell, struct termios *oldt)
{
    ssize_t byte_read = 0;
    char c = 0;

    shell->cursor_pos = 0;
    shell->args_len = 0;
    shell->line = malloc(sizeof(char) * 1024);
    if (!shell->line)
        return 84;
    byte_read = read(STDIN_FILENO, &c, 1);
    while (byte_read > 0 && c != '\n' && c != 4) {
        arrows_key(shell, shell->history, c);
        fflush(stdout);
        byte_read = read(STDIN_FILENO, &c, 1);
    }
    my_printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
    return error_case(c, byte_read);
}

int getinput_gest(shell_t *shell, char **env)
{
    struct termios oldt;
    struct termios newt;

    shell->line = NULL;
    if (init_output(&newt, &oldt) == -1)
        return 84;
    read_loop(shell, &oldt);
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
