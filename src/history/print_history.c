/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** print_history
*/

#include "my_sh.h"

void free_lines(char **lines)
{
    int i;

    i = 0;
    while (i < MAX_LINES) {
        if (lines[i])
            free(lines[i]);
        i++;
    }
}

void print_lines(char **lines, int total)
{
    int start;
    int i;
    int index;
    int limit;

    start = total >= MAX_LINES ? total % MAX_LINES : 0;
    limit = total >= MAX_LINES ? MAX_LINES : total;
    i = 0;
    while (i < limit) {
        index = (start + i) % MAX_LINES;
        printf("%s", lines[index]);
        i++;
    }
}

void read_last_lines(FILE *file, char **lines, int *total)
{
    char *line;
    size_t len;
    ssize_t read;
    int count;
    int i;

    line = NULL;
    len = 0;
    count = 0;
    read = getline(&line, &len, file);
    while (read != -1) {
        i = count % MAX_LINES;
        if (lines[i])
            free(lines[i]);
        lines[i] = strdup(line);
        count = count + 1;
        read = getline(&line, &len, file);
    }
    *total = count;
    free(line);
}

int print_history(void)
{
    FILE *file;
    char *lines[MAX_LINES];
    int i;
    int total;

    i = 0;
    while (i < MAX_LINES) {
        lines[i] = NULL;
        i++;
    }
    file = fopen(".history", "r");
    if (!file)
        return 84;
    read_last_lines(file, lines, &total);
    print_lines(lines, total);
    free_lines(lines);
    fclose(file);
    return 0;
}
