/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 08:58:34 by kslik             #+#    #+#             */
/*   Updated: 2023/04/28 09:13:13 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int stln(char **nature, int i)
{
    int j = 0;
    while(nature[i][j] != '\0')
        j++;
    return(j);
}
char **my_env(char **nature)
{
    int i = 0;
    int l = 0;
    int j = 0;
    char **my_env;
    while(nature[i])
        i++;
    my_env = malloc(i * sizeof(char **));
    i =0;
    while(nature[i][j] != '\0')
    {
        j = 0;
        l = stln(nature, i);
        my_env[i] = malloc(l * sizeof(char *));
        while(nature[i][j] != '\0')
        {
            my_env[i][j] = nature[i][j];
            j++;
        }
        my_env[i][j] = '\0';
        i++;
    }
    return (my_env);
}
