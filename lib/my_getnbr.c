/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_getnbr
*/

int my_getnbr(char const *str)
{
    long long int result = 0;
    int i = 0;
    int signe = 1;

    for (i; str[i] == '+' || str[i] == '-'; i++)
        if (str[i] == '-')
            signe = - signe;
    for (i; str[i] <= '9' && str[i] >= '0'; i++) {
        result = result * 10 + (str[i] - 48);
        if (result * signe > 2147483647 || result * signe < -2147483648)
            return 0;
    }
    return result * signe;
}
