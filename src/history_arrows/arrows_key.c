/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** arrows_key
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

void check_arrows(char buff, shell_t *shell, history_t *hist)
{
    int tmp_index = hist->index;

    buff = getchar();
    switch (buff) {
        case 'A':
            tmp_index = history_up(shell, tmp_index);
            break;
        case 'B':
            tmp_index = history_down(shell, hist, tmp_index);
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

int arrows_key(shell_t *shell, history_t *hist)
{
    char buff;

    termios_init();
    if (read(STDIN_FILENO, &buff, 1) <= 0) {
        termios_reset();
        exit(84);
    }
    console_log(stdout, "%c", buff);
    if (buff == '\033')
        check_arrows(buff, shell, hist);
    if (buff == '\n') {
        console_log(stdout, "\nenter!\n");
        return 0;
    }
    termios_reset();
    return 0;
}
