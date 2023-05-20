/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:35:07 by kslik             #+#    #+#             */
/*   Updated: 2023/05/20 18:55:52 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <string.h>
void *strcp_dl3bar(char *dec, char *dp)
{
	int i = 0;
	while(dp[i] != '\0')
	{
		dec[i] = dp[i];
		i++;
	}
	dec[i] = '\0';
	return(dec);
}
char **exp_no_opt(char **env)
{
	int i = 0;
	int j = 0;
	int fl = 0;
	int l = 0;
    int p = 0;
	int q = 0;
	char dec[20];
	strcp_dl3bar(dec, "declare -x ");
	char **new_env;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char **) * i + 1);
	i = 0;
	while(env[i])
	{
        p = 0;
		fl = 0;
		j = 0;
		q = 0;
		l = ft_strlen(env[i]);
		new_env[i] = malloc((sizeof(char *) * l) + 15);
		while(j < 11)
		{
			new_env[i][j] = dec[j];
			j++;
		}
		while (env[i][q])
		{
			if(env[i][q - 1] == '=' && fl == 0)
			{
                p++;
				new_env[i][j++] = '"';
				fl = 1;
			}
			new_env[i][j] = env[i][q];
			j++;
			q++;
		}
        if(p != 0 || env[i][q - 1] == '=')
        {
		    new_env[i][j++] = '"';
		    if(fl != 1)
			    new_env[i][j++] = '"';
        }
		new_env[i][j] = '\0';
		i++;
	}
	new_env[i] = NULL;
	return(new_env);
}