/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntranc <luntranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:57:21 by luntranc          #+#    #+#             */
/*   Updated: 2023/12/03 17:07:04 by luntranc         ###   ########.fr       */
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
    ret = malloc(len * sizeof(char) + 2); // "1 3 2" 2 "   \0" "132"
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
    int len;
    int index;
    int x;
    int y;
    int str_index;
    int max;

    len = ft_strlen(str);
    mat = malloc((int)(len / 4) * sizeof(int *) + 1);
    index = 0;
    while (index <= len / 4)
    {
        mat[index] = malloc(4 * sizeof(int));
        index++;
    }
    x = 0;
    y = 0;
    str_index = 0;
    max = 4;
    while (y < len / 4 -1 || str_index < ft_strlen(str))
    {
        while (x < max)
        {
            if (str_index < 8)
            {
                if (str_index < 4)
                {
                    mat[0][x] = str[str_index] - '0';
                }
                else
                {
                    mat[3][x] = str[str_index] - '0';
                }
            }
            else
            {
                if (str_index == 8)
                {
                    y--;
                }
                mat[y][x] = str[str_index] - '0';
            }
            x++;
            str_index++;
        }
        y++;
        x = 0;
    }
    return mat;
}

void print_matrix(int **mat, int col, int row)
{
    int x;
    int y;
    
    x = 0;
    y = 0;

    while(y < row)
    {
        while (x < col)
        {
            ft_putchar(mat[y][x] + '0');
            ft_putchar(' ');
            x++;
        }
        y++;
        x = 0;
        ft_putchar('\n');
    }
}

int *array_gen(int first, int last)
{
    int *ret;
    int index;
    int writeable;
    int iter;
    int changes;

    ret = malloc(6 * sizeof(int));
    index = 1;
    writeable = 0;
    iter = 1;
    changes = 0;
    if (!ret)
    {
        return (0);
    }
    if ((first + last) != 5 && (first < 0 && last < 0))
    {
        ft_putstr("Error: Combinacion invalida");
        return (0);
    }
    
    while(index < 5)
    {
        if ( index > 1 && ret[index - 1] > writeable)
        {
            iter = 1;
            while (iter < 5 && changes)
            {
                if (iter == 1)
                    changes = 0;
                if (iter == 5)
                    iter = 1;
                if (ret[iter] == writeable)
                {
                    writeable--;
                    changes++;
                }
                iter++;
            }
            ret[index] = writeable;
            if (writeable == 1)
            {
                writeable++;
            }
            else
            writeable--;
        }
        if (index > 1 && ret[index - 1] < writeable)
        {
            iter = 1;
            while (iter < 5 && changes)
            {
                if (iter == 1)
                    changes = 0;
                if (iter == 5)
                    iter = 1;
                if (ret[iter] == writeable)
                {
                    writeable++;
                    changes++;
                }
                iter++;
            }
            ret[index] = writeable;
            if (writeable == 4)
            {
                writeable--;
            }
            else
            writeable++;
        }
        if (first == 4 && index == 1)
        {
            ret[index] = 1;
            writeable = 2;
        }
        if (first == 3 && index == 1)
        {
            ret[index] = 2;
            writeable = 3;
        }
        if (first == 2 && index == 1)
        {
            ret[index] = 3;
            writeable = 4;
        }
        if (first == 1 && index == 1)
        {
            ret[index] = 4;
            writeable = 3;
        }
        index++;
    }
    ret[0] = first;
    ret[5] = last;
    return ret;
}

int **algoritmo(int **mat)
{
    int y;

    y = 1;
    while(y < 5)
    {
        mat[y] = array_gen(mat[y][0], mat[y][5]);
        y++;
    }
    return mat;
}

void mat_malloc(int ***mat, int rows, int col)
{
    int index;

    index = 0;
    *mat = malloc(rows * sizeof(int*));
    while (index < rows)
    {
        (*mat)[index] = malloc(col * sizeof(int));
        index++;
    }
}

int main(int argc, char *argv[])
{
    char *a;
    int **input_mat;
    int **out_mat;

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
    input_mat = create_int_matrix(a);
    free(a);
    if (!input_mat)
    {
        ft_putstr("Error: error al alocar memoria\n");
        return (1);
    }
    print_matrix(input_mat, 4, 4);
    mat_malloc(&out_mat, 4, 4);
    print_matrix(out_mat, 4, 4);
}
