/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** handle_specific_case_read
*/

#include "my.h"
#include "my_sh.h"

int init_output(struct termios *newt, struct termios *oldt)
{
    if (tcgetattr(STDIN_FILENO, oldt) == -1)
        return -1;
    *newt = *oldt;
    newt->c_lflag &= ~(ICANON | ECHO);
    newt->c_cc[VMIN] = 1;
    newt->c_cc[VTIME] = 0;
    return tcsetattr(STDIN_FILENO, TCSANOW, newt);
}
