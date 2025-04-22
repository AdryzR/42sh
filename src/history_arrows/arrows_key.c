/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** arrows_key
*/

#include "my_sh.h"
#include "my.h"

static void termios_init(void)
{
    struct termios t;

    tcgetattr(0, &t);
    t.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &t);
}

static void termios_reset(void)
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

int arrows_key(shell_t *shell, history_t *hist, char c)
{
    console_log(stdout, "%c", c);
    if (c == '\033')
        check_arrows(c, shell, hist);
    return 0;
}
