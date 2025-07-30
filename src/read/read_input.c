/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

static char *error_case(char c, ssize_t byte_read, char *line)
{
    if (c == 4) {
        free(line);
        return NULL;
    }
    if (byte_read <= 0) {
        free(line);
        return NULL;
    }
    if (c == '\n' && strlen(line) == 0)
        line[0] = '\n';
    write(0, "\n", 1);
    return line;
}

void set_struct_values(shell_t *shell)
{
    if (shell->alloc)
        free(shell->alloc);
    if (shell->line) {
        free(shell->line);
        shell->line = NULL;
    }
    shell->alloc = malloc(sizeof(alloc_t));
    shell->alloc->nb_alloc = 10;
    shell->alloc->nb_char = 10;
    shell->cursor_pos = 0;
    shell->args_len = 0;
}

char *realloc_size(char *line, alloc_t *alloc)
{
    char *tmp;

    alloc->nb_char++;
    if (alloc->nb_char >= (alloc->nb_alloc - 1)) {
        tmp = realloc(line, alloc->nb_alloc * 2);
        if (!tmp)
            return line;
        alloc->nb_alloc *= 2;
        return tmp;
    }
    return line;
}

char *read_loop(shell_t *shell, struct termios *oldt, char *line)
{
    ssize_t byte_read = 0;
    char c = 0;

    set_struct_values(shell);
    line = calloc(10, sizeof(char));
    if (!line)
        return NULL;
    byte_read = read(STDIN_FILENO, &c, 1);
    while (byte_read > 0 && c != '\n' && c != 4) {
        line = realloc_size(line, shell->alloc);
        line = arrows_key(shell, shell->history, c, line);
        fflush(stdout);
        byte_read = read(STDIN_FILENO, &c, 1);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
    return error_case(c, byte_read, line);
}

char *read_line(shell_t *shell)
{
    struct termios oldt;
    struct termios newt;
    char *line = NULL;

    shell->history->tmp_index = shell->history->index;
    if (init_output(&newt, &oldt) == -1)
        return NULL;
    line = read_loop(shell, &oldt, line);
    fflush(stdout);
    if (!line) {
        line = malloc(sizeof(char));
        if (!line) {
            return NULL;
        }
        line[0] = '\0';
    }
    return line;
}
