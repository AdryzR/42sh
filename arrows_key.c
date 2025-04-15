/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** ex02.c
*/

#include "my_sh.h"
#include "my.h"
 
static void termios_init()
{
    struct termios t;

    tcgetattr(0, &t);
    t.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &t);
}

static void termios_reset()
{
    struct termios t;

    tcgetattr(0, &t);
    t.c_cflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void console_log(FILE *stream, const char *restrict format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);
    fflush(stream);
}

void check_arrows(char buff, shell_t *shell)
{
    buff = getchar();
    switch (buff) {
        case 'A':
            history_up(shell);
            break;
        case 'B':
            history_down(shell);
            break;
        case 'C':
            printf("\033[C");
            break;
        case 'D':
            printf("\033[D");
            break;
    }
    fflush(stdout);
}

int arrows_key(shell_t *shell)
{
    char buff;

    termios_init();
    while (42) {
        if (read(STDIN_FILENO, &buff, 1) <= 0) {
            termios_reset();
            exit(84);
        }
        console_log(stdout, "%c", buff);
        if (buff == '[')
            check_arrows(buff, shell);
        if (buff == '\n') {
            console_log(stdout, "\nenter!\n");
            break;
        }
    }
    termios_reset();
    return 0;
}
