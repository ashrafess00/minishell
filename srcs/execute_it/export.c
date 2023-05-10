/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:58:55 by kslik             #+#    #+#             */
/*   Updated: 2023/05/10 18:00:11 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char **our_realloc_v2(char **arr, char *new, int index, int bol)
{
	int i = 0;
	int l = 0;
	int j = 0;
	int c = 0;
	int q;
	char **new_arr;
	while(arr[i] != '\0')
		i++;
	q = i;
	i += 1;
	new_arr = malloc(i * sizeof(char **) + bol);
	i = 0;
	while(i < q)
	{
		j = 0;
		l = stln(arr, i) + 1;
		new_arr[i] = malloc(l * sizeof (char *));
		while(arr[i][j] != '\0')
		{
			new_arr[i][j] = arr[i][j];
			j++;
		}
		new_arr[i][j] = '\0';
		i++;
	}
	l = strlne(new);
	if(bol == 1)
	{
		j= 0;
		new_arr[i] = malloc(l * sizeof (char *) + 1);
		while(new[j] != '\0')
		{
			new_arr[i][j] = new[j];
			j++;
		}
	}
	else
	{
		while(new[c] != '\0')
		{
			new_arr[index][c] = new[c];
			c++;
		}
		new_arr[index][c] = '\0';
	}
	if(bol == 1)
	{
		new_arr[i][j] = '\0';
		i++;
		new_arr[i] = NULL;
	}
	free(arr);
	return(new_arr);
}
char *space_err(char *var)
{
	int i = 0;
	int q= 0;
	char *err ;
	int k = 0;
	while(var[k])
		k++;
	while(var[k] != '=')
		k--;
	err = malloc(k + 3);
	while(k > 0)
	{
		if(var[k + 1] == ' ' || var[k + 1] == '\0')
		{
			err = malloc(sizeof(char *) *  k + 3);
			while(q <= k)
			{
				err[q] = var[q];
				q++;
			}
		}
		k--;
	}
	err[q] = var[q];
	err[q + 1] = '\0';
	
	return(err);
}
char **exp_no_opt(char **env)
{
	int i = 0;
	int j = 0;
	int fl = 0;
	int l = 0;
	int q = 0;
	char dec[20];
	strcpy(dec, "declare -x ");//////3ndak tnsa hadi
	char **new_env;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char **) * i + 1);
	i = 0;
	while(env[i])
	{
		fl = 0;
		j = 0;
		q = 0;
		l = strlne(env[i]);
		new_env[i] = malloc((sizeof(char *) * l) + 15);
		while(j < 11)
		{
			new_env[i][j] = dec[j];
			j++;
		}
		while (env[i][q])
		{
			if(env[i][q - 1] == '=')
			{
				new_env[i][j++] = '"';
				fl = 1;
			}
			new_env[i][j] = env[i][q];
			j++;
			q++;
		}
		new_env[i][j++] = '"';
		if(fl != 1)
			new_env[i][j++] = '"';
		new_env[i][j] = '\0';
		i++;
	}
	new_env[i] = NULL;
	return(new_env);
}
int exp_er(char *ljadid)
{
	int plus = 0;
	int i = 0;
	while(ljadid[i] != '\0')
	{
		if(ljadid[i] == '=')
			plus++;
		i++;
	}
	if(plus <= 0)
		return(0);
	return(1);
}
int spc_err(char *var)
{
	int i  = 0;
	while(var[i] != '\0')
	{
		if(var[i] == ' ')
			return(1);
		i++;
	}
	return 0;
}
char **export(char **env, char *ljadid)
{
	if(!ljadid)
		return (exp_no_opt(env));
	if(exp_er(ljadid) == 0)
	{
		printf("syntax error\n");
		return(env);
	}
	if(spc_err(ljadid) == 1)
		ljadid = space_err(ljadid);
	int i = 0;
	int j = 0;
	int n = 0;
	while(env[i] != '\0')
	{
		if(env[i][j] == ljadid[j])
		{
			while(ljadid[n] != '=')
			{
				if(env[i][n] != ljadid[n])
				{
					n = 100;
					break;
				}
				n++;
			}
			if(n != 100)
			{
				env = our_realloc_v2(env, ljadid, 0, 0);
				return(env);
			}
			j++;
		}
		i++;
	}
	env = our_realloc_v2(env, ljadid, 0, 1);
	return env;
}
char **unset_hel(char **env, char *var, int i)
{
	int j = 0;
	int l = 0;
	int inde = 0;
	int ji = 0;
	char **new_env;
	while(env[j])
		j++;
	new_env = malloc(sizeof(char **) * j + 1);
	j = 0;
	while(env[j] != '\0')
	{
		if(j != i)
		{
			ji = 0;
			l = strlne(env[j]);
			new_env[inde] = malloc(sizeof(char *) * l + 1);
			while(env[j][ji] != '\0')
			{
				new_env[inde][ji] = env[j][ji];
				ji++;
			}
			new_env[inde][ji] = '\0';
			inde++;
		}
		j++;
	}
	new_env[inde] = NULL;	
	return (new_env);
}
char **unset(char **env, char *var)
{
	int i = 0;
	int j = 0;
	int n = 0;
	if(!var)
		return(env);
	while(env[i])
	{
		if(env[i][j] == var[j])
		{
			while(var[j])
			{
				if(env[i][j + 1] == '=') 
				{
					while(var[n])
					{
						if(env[i][n] != var[n])
						{
							n = 100;
							break;
						}
						n++;
					}
					if(n != 100)
					{
						env = unset_hel(env, var, i);
						return(env);
					}
				}
				j++;
			}
			j++;
		}
		i++;
	}
	return(env);
}