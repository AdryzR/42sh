/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** handle_specific_case_read
*/

#include "my.h"
#include "my_sh.h"

int init_output(shell_t *shell, struct termios newt, struct termios oldt)
{
    if (!shell)
        return 84;
    if (isatty(STDIN_FILENO))
        my_putstr("> ");
    if (tcgetattr(STDIN_FILENO, &oldt) == -1)
        return 84;
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1)
        return 84;
}

int specific_case(char c, char *line)
{
    if (c == 4)
        exit(84);
    if (c == '\n')
        return 2;
    // if (arrows_key(shell, shell->history, c) == 0)
    //     continue;
    if (c == 10)
        return 1;
    if (c == 127) {
        // implement backspace logic here if needed
        return 1;
    }
    return 0;
}
