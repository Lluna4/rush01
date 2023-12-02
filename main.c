/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntranc <luntranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:57:21 by luntranc          #+#    #+#             */
/*   Updated: 2023/12/01 23:03:16 by luntranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int ret;

    ret = 0;
    while (str[ret])
        ret++;

    return ret;
}

void ft_putchar(char a)
{
    write(1, &a, 1);
}

void ft_putstr(char *str)
{
    while (*str != '\0')
    {
        ft_putchar(*str);
        str++;
    }
}

int charlen(char *str, char ch)
{
    int ret;
    int index;
    int ch_before;

    index = 0;
    ret = 0;
    while (str[index] != '\0')
    {
        if (str[index] == ch && ch_before == 0)
        {
            ret++;
            ch_before = 1;
        }
        else if (str[index] != ch)
        {
            ch_before = 0;
        }
        index++;
    }
    return ret;
}

char *split(char *str)
{
    int len;
    char *ret;
    int index;
    int ret_index;
    char buffer;

    if (str[0] == ' ')
        return(NULL);

    index = 0;
    ret_index = 0;
    len = charlen(str, ' ');
    if (len == 0)
    {
        ft_putstr("Error: no hay espacios vacios\n");
        return (NULL);
    }
    ret = malloc(len * sizeof(char) + 2);
    if (!ret)
    {
        ft_putstr("Error: error al alocar memoria\n");
        return (NULL);
    }
    while (1)
    {
        if ((str[index] == ' ' && str[index - 1] != ' ') || str[index] == '\0')
        {
            ret[ret_index] = buffer;
            if (str[index] == '\0')
                break;
            ret_index++;
        }
        else
        {
            if (index > 1 && buffer == str[index - 1])
            {
                return (NULL);
            }
            buffer = str[index];
        }
        index++;
    }
    ret[len+2] = '\0';
    return ret;
}

int **create_int_matrix(char *str)
{
    int **mat;
    int index;
    int x;
    int y;
    
    index = 0;
    x = 0;
    y = 0;
    mat = malloc(6 * sizeof(int *));
    if (!mat)
    {
        return (0);
    }
    while (index < 6)
    {
        mat[index] = malloc(6 * sizeof(int));
        if (!mat[index])
            return (0);
        index++;
    }
    index = 0;
    while (x < 6 && y < 6)
    {
        if (x == 0 || x == 5)
            mat[y][x] = 0;
        else
        {
            mat[y][x] = str[index] - '0';
            index++;
        }
        x++;
        if (x == 6)
        {
            y += 5;
            x = 0;
        }
    }
    y = 1;
    while (x <= 5)
    {
        if (x == 0 || x == 5)
        {
            mat[y][x] = str[index] - '0';
            index++;
        }
        else
            mat[y][x] = 0;
        y++;
        if (y == 5)
        {
            x ++;
            y = 1;
        }
    }   
    return mat;
}

void print_matrix(int **mat)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < 6)
    {
        if ((y == 0 || y == 5) && (x == 0 || x == 5))
            ft_putchar(' ');
        else
            ft_putchar(mat[y][x] + '0');
        x++;
        if (x == 6)
        {
            ft_putchar('\n');
            y++;
            x = 0;
        }
        else
            ft_putchar(' ');
    }
}

int main(int argc, char *argv[])
{
    char *a;
    int **mat;

    if (argc < 2)
    {
        ft_putstr("Error: No hay suficientes argumentos\n");
        return(1);
    }
    
    a = split(argv[1]);

    if (!a)
    {
        return (1);
    }
    if (ft_strlen(a) != 16)
    {
        ft_putstr("Error: No hay suficientes numeros\n");
        free(a);
        return (1);
    }
    mat = create_int_matrix(a);
    free(a);
    if (!mat)
    {
        ft_putstr("Error: error al alocar memoria\n");
        return (1);
    }
    print_matrix(mat);
}
