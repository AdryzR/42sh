/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** arrows_key
*/

#include "my_sh.h"
#include "my.h"

static char *handle_suppr_char(shell_t *shell, char *line)
{
    if (shell->cursor_pos >= shell->args_len)
        return line;
    for (int i = shell->cursor_pos; i < shell->args_len - 1; ++i)
        line[i] = line[i + 1];
    shell->args_len--;
    line[shell->args_len] = '\0';
    write(STDOUT_FILENO, "\033[s", 3);
    write(STDOUT_FILENO, "\033[K", 3);
    write(STDOUT_FILENO, &line[shell->cursor_pos],
    shell->args_len - shell->cursor_pos);
    write(STDOUT_FILENO, " ", 1);
    write(STDOUT_FILENO, "\033[u", 3);
    return line;
}

char *check_arrows(char buff, shell_t *shell, history_t *hist, char *line)
{
    // int tmp_index = hist->index;

    buff = getchar();
    switch (buff) {
        case 'A':
            // tmp_index = history_up(shell, tmp_index);
            break;
        case 'B':
            // tmp_index = history_down(shell, hist, tmp_index);
            break;
        case 'C':
            if (shell->cursor_pos < shell->args_len) {
                dprintf(STDOUT_FILENO, "\033[C");
                shell->cursor_pos++;
            }
            break;
        case 'D':
            if (shell->cursor_pos > 0) {
                dprintf(STDOUT_FILENO, "\033[D");
                shell->cursor_pos--;
            }
            break;
        case '3':
            buff = getchar();
            if (buff == '~')
                line = handle_suppr_char(shell, line);
            break;
    }
    return line;
}

static char *handle_delete_char(shell_t *shell, char *line)
{
    if (shell->args_len < 1 || shell->cursor_pos < 1)
        return line;
    for (int i = shell->cursor_pos - 1; i < shell->args_len - 1; i++)
        line[i] = line[i + 1];
    shell->args_len--;
    shell->cursor_pos--;
    line[shell->args_len] = '\0';
    write(STDOUT_FILENO, "\b", 1);
    write(STDOUT_FILENO, "\033[s", 3);
    write(STDOUT_FILENO, "\033[K", 3);
    write(STDOUT_FILENO, &line[shell->cursor_pos],
    shell->args_len - shell->cursor_pos);
    write(STDOUT_FILENO, " ", 1);
    write(STDOUT_FILENO, "\033[u", 3);
    return line;
}

static char *handle_input_char(shell_t *shell, char c, char *line)
{
    for (int i = shell->args_len; i > shell->cursor_pos; i--)
        line[i] = line[i - 1];
    line[shell->cursor_pos] = c;
    shell->args_len++;
    shell->cursor_pos++;
    line[shell->args_len] = '\0';
    write(STDOUT_FILENO, "\033[s", 3);
    write(STDOUT_FILENO, "\033[K", 3);
    write(STDOUT_FILENO, &line[shell->cursor_pos - 1],
    shell->args_len - shell->cursor_pos + 1);
    write(STDOUT_FILENO, "\033[u", 3);
    write(0, &c, 1);
    return line;
}

char *arrows_key(shell_t *shell, history_t *hist, char c, char *line)
{
    if (c == 127) {
        line = handle_delete_char(shell, line);
        return line;
    }
    if (c == '\033') {
        if (read(STDIN_FILENO, &c, 1) == 0)
            return line;
        if (c == '[') {
            line = check_arrows(c, shell, hist, line);
            return line;
        }
    }
    line = handle_input_char(shell, c, line);
    return line;
}
