/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** handle_specific_case_read
*/

#include "my.h"
#include "my_sh.h"

int init_output(shell_t *shell, struct termios *newt, struct termios *oldt)
{
    oldt = malloc(sizeof(struct termios));
    newt = malloc(sizeof(struct termios));
    tcgetattr(STDIN_FILENO, oldt);
    newt = oldt;
    newt->c_lflag &= ~(ICANON | ECHO);
    newt->c_cc[VMIN] = 1;
    newt->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, newt);
    return 0;
}

