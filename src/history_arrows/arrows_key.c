/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** arrows_key
*/

#include "my_sh.h"
#include "my.h"

void check_arrows(char buff, shell_t *shell, history_t *hist)
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
    }
}

int arrows_key(shell_t *shell, history_t *hist, char c)
{
    if (c == 127 && shell->args_len > 0) {
        shell->args_len--;
        shell->line[shell->args_len] = '\0';
        write(STDOUT_FILENO, "\b \b", 3);
        return 0;
    }
    if (c == '\033') {
        check_arrows(c, shell, hist);
        return 0;
    }
    shell->line[shell->args_len] = c;
    shell->line[shell->args_len + 1] = '\0';
    shell->args_len++;
    shell->cursor_pos++;
    write(0, &c, 1);
    return 0;
}
