/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

static char *error_case(char c, ssize_t byte_read, char *line)
{
    if (c == 4)
        exit(0);
    if (byte_read <= 0)
        return NULL;
    return line;
}

char *read_loop(shell_t *shell, struct termios *oldt, char *line)
{
    ssize_t byte_read = 0;
    char c = 0;

    shell->cursor_pos = 0;
    shell->args_len = 0;
    line = malloc(sizeof(char) * 1024);
    if (!line)
        return NULL;
    byte_read = read(STDIN_FILENO, &c, 1);
    while (byte_read > 0 && c != '\n' && c != 4) {
        line = arrows_key(shell, shell->history, c, line);
        fflush(stdout);
        byte_read = read(STDIN_FILENO, &c, 1);
    }
    my_printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
    return error_case(c, byte_read, line);
}

char *read_line(shell_t *shell, char **env)
{
    struct termios oldt;
    struct termios newt;
    char *line = NULL;

    shell->history->tmp_index = shell->history->index;
    if (init_output(&newt, &oldt) == -1)
        return NULL;
    line = read_loop(shell, &oldt, line);
    fflush(stdout);
    if (!line) {
        line = malloc(sizeof(char));
        if (!line) {
            return NULL;
        }
        line[0] = '\0';
    }
    return line;
}
