/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

int read_loop(shell_t *shell, struct termios *oldt)
{
    shell->cursor_pos = 0;
    shell->args_len = 0;
    ssize_t byte_read = 0;
    char c = 0;

    shell->line = malloc(sizeof(char) * 1024);
    if (!shell->line)
        return 84; // handle malloc fail
    byte_read = read(STDIN_FILENO, &c, 1);
    while (byte_read > 0 && c != '\n' && c != 4) {
        arrows_key(shell, shell->history, c);  // <-- ONLY handle inside arrows_key
        fflush(stdout);
        byte_read = read(STDIN_FILENO, &c, 1);
    }
    printf("\n");
    if (c == 4)
        exit(0);
    if (byte_read <= 0)
        return 84;
    return 0;
}

int getinput_gest(shell_t *shell, char **env)
{
    struct termios *oldt;
    struct termios *newt;

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
