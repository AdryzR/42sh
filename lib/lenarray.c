/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** lenarray
*/

#include "my.h"

int len_array(char **array)
{
    size_t i = 0;

    if (!array)
        return 0;
    while (array[i])
        ++i;
    return i;
}
