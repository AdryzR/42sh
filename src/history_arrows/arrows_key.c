/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** arrows_key
*/

#include "my_sh.h"
#include "my.h"

void check_arrows_l_r(char buff, shell_t *shell, history_t *hist)
{
    switch (buff) {
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
    }
}

void check_arrows_u_d(char buff, shell_t *shell, history_t *hist)
{
    buff = getchar();
    switch (buff) {
        case 'A':
            history_up(shell, hist);
            break;
        case 'B':
            history_down(shell, hist);
            break;
        default:
            return check_arrows_l_r(buff, shell, hist);
    }
}

static void handle_delete_char(shell_t *shell)
{
    if (shell->args_len < 1 || shell->cursor_pos < 1)
        return;
    for (int i = shell->cursor_pos - 1; i < shell->args_len - 1; i++)
        shell->line[i] = shell->line[i + 1];
    shell->args_len--;
    shell->cursor_pos--;
    shell->line[shell->args_len] = '\0';
    write(STDOUT_FILENO, "\b", 1);
    write(STDOUT_FILENO, "\033[s", 3);
    write(STDOUT_FILENO, "\033[K", 3);
    write(STDOUT_FILENO, &shell->line[shell->cursor_pos],
    shell->args_len - shell->cursor_pos);
    write(STDOUT_FILENO, " ", 1);
    write(STDOUT_FILENO, "\033[u", 3);
}

static void handle_input_char(shell_t *shell, char c)
{
    for (int i = shell->args_len; i > shell->cursor_pos; i--)
        shell->line[i] = shell->line[i - 1];
    shell->line[shell->cursor_pos] = c;
    shell->args_len++;
    shell->cursor_pos++;
    shell->line[shell->args_len] = '\0';
    write(STDOUT_FILENO, "\033[s", 3);
    write(STDOUT_FILENO, "\033[K", 3);
    write(STDOUT_FILENO, &shell->line[shell->cursor_pos - 1],
    shell->args_len - shell->cursor_pos + 1);
    write(STDOUT_FILENO, "\033[u", 3);
    write(0, &c, 1);
}

int arrows_key(shell_t *shell, history_t *hist, char c)
{
    if (c == 127) {
        handle_delete_char(shell);
        return 0;
    }
    if (c == '\033') {
        if (read(STDIN_FILENO, &c, 1) == 0)
            return 0;
        if (c == '[') {
            check_arrows_u_d(c, shell, hist);
            return 0;
        }
    }
    handle_input_char(shell, c);
    return 0;
}
