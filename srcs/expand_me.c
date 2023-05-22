/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_me.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:56:39 by kslik             #+#    #+#             */
/*   Updated: 2023/05/22 13:51:31 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	search_ky_2(struct s_expand *exp)
{
	exp->i = 0;
	while (exp->tmp->val[exp->i] != '=' && exp->tmp->val[exp->i])
		exp->i++;
	exp->i++;
	while (exp->tmp->val[exp->i] != '\0')
	{
		exp->result[exp->resultIndex] = exp->tmp->val[exp->i];
		exp->i++;
		exp->resultIndex++;
	}
}

void	search_key(char *input, struct s_expand *exp, int c)
{
	if (c == 0)
	{
		while (input[exp->inputIndex] == '$' && input[exp->inputIndex] != '\0')
			exp->inputIndex++;
		while (((input[exp->inputIndex] >= 97 && input[exp->inputIndex] <= 122)
				|| (input[exp->inputIndex] >= 65
					&& input[exp->inputIndex] <= 90)) && input[exp->inputIndex])
		{
			exp->pedi[exp->c] = input[exp->inputIndex];
			exp->inputIndex++;
			exp->c++;
		}
		exp->pedi[exp->c] = '\0';
	}
	else if (c == 1)
		search_ky_2(exp);
}

void	inist_to_zero(struct s_expand *exp, int c, char *input)
{
	if (c == 0)
	{
		exp->c = 0;
		exp->i = 0;
		free_pedi(exp->pedi);
	}
	if (c == 1)
	{
		exp->result[exp->resultIndex] = input[exp->inputIndex];
		exp->resultIndex++;
		exp->inputIndex++;
	}
}

void	idont_know_what_mdoin(struct s_expand *exp, int c, char *input,
		t_my_env *my_env)
{
	if (c == 0)
	{
		exp->brek = 0;
		search_key(input, exp, 0);
		exp->tmp = my_env;
		while (exp->tmp != NULL)
		{
			exp->i = 0;
			while (exp->tmp->val[exp->i] != '\0' && exp->pedi[exp->i] != '\0'
				&& exp->tmp->val[exp->i] == exp->pedi[exp->i])
				exp->i++;
			if (exp->pedi[exp->i] == '\0')
			{
				search_key(input, exp, 1);
				exp->brek = 1;
				break ;
			}
			exp->tmp = exp->tmp->next;
		}
	}
}

char	*expandini(char *input, t_my_env *my_env, int exit_code)
{
	struct s_expand	exp;
	char			*ex;

	ex = ft_itoa(exit_code);
	ex_data(&exp);
	exp.i = 0;
	calcul_c(input, &exp, 0, ex);
	exp.result = ft_calloc(strlen(input) + (exp.c * 87) + 1, 1);
	while (input[exp.inputIndex] != '\0')
	{
		calcul_c(input, &exp, 1, ex);
		if (input[exp.inputIndex] == '$' && exp.fl == 0)
		{
			inist_to_zero(&exp, 0, input);
			if (input[exp.inputIndex + 1] == '?')
				calcul_c(input, &exp, 2, ex);
			else
				idont_know_what_mdoin(&exp, 0, input, my_env);
		}
		else if (input[exp.inputIndex] != '\0')
			inist_to_zero(&exp, 1, input);
	}
	free(input);
	free(ex);
	return (exp.result);
}
