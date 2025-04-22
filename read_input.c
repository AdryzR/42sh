/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** read_input
*/

#include "my.h"
#include "my_sh.h"

int realloc_input(shell_t *shell, size_t args_len, struct termios oldt)
{
    char *temp = NULL;

    temp = realloc(shell->line, sizeof(char) * (args_len + 2));
        if (!temp) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            free(shell->line);
            return ret_and_set_status(84, shell);
    }
    shell->line = temp;
    return 0;
}

int read_loop(shell_t *shell, struct termios oldt)
{
    size_t args_len = 0;
    ssize_t byte_read = 0;
    char c = 0;

    byte_read = read(STDIN_FILENO, &c, 1);
    while (byte_read > 0 && c != '\n' && c != 4) {
        specific_case(c, shell->line);
        // check si last char == 127 si oui realloc - 1
        realloc_input(shell, args_len, oldt);
        shell->line[args_len] = c;
        shell->line[args_len + 1] = '\0';
        args_len++;
        byte_read = read(STDIN_FILENO, &c, 1);
    }
    if (c == 4)
        exit(84);
    if (byte_read == 0)
        exit(84);
    if (c == 10)
        return 0;
}

int getinput_gest(shell_t *shell, char **env)
{
    struct termios oldt, newt;

    shell->line = NULL;
    init_output(shell, newt, oldt);
    read_loop(shell, oldt);
    fflush(stdout);
    if (!shell->line) {
        shell->line = malloc(sizeof(char));
        if (!shell->line) {
            return 84;
        }
    shell->line[0] = '\0';
    }
    return 0;    
}
