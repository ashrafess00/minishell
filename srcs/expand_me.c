/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_me.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:56:39 by kslik             #+#    #+#             */
/*   Updated: 2023/06/02 19:39:36 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_ky_2(struct s_expand *exp)
{
	exp->i = 0;
	while (exp->tmp->val[exp->i] != '=' && exp->tmp->val[exp->i])
		exp->i++;
	exp->i++;
	while (exp->tmp->val[exp->i] != '\0')
	{
		exp->result[exp->result_index] = exp->tmp->val[exp->i];
		exp->i++;
		exp->result_index++;
	}
}

void	search_key(char *input, struct s_expand *exp, int c)
{
	if (c == 0)
	{
		while (input[exp->input_index] == '$'
			&& input[exp->input_index] != '\0')
			exp->input_index++;
		while (((input[exp->input_index] >= 97
					&& input[exp->input_index] <= 122)
				|| (input[exp->input_index] >= 65
					&& input[exp->input_index] <= 90))
			&& input[exp->input_index])
		{
			exp->pedi[exp->c] = input[exp->input_index];
			exp->input_index++;
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
		exp->result[exp->result_index] = input[exp->input_index];
		exp->result_index++;
		exp->input_index++;
	}
}

static int	check_inp(char *input, struct s_expand exp)
{
	if (input[exp.input_index] == '$' && exp.fl == 0
		&& ((ft_isalpha(input[exp.input_index + 1])
				|| input[exp.input_index + 1] == '?')))
		return (1);
	return (0);
}

char	*expandini(char *input, t_my_env *my_env, int exit_code)
{
	struct s_expand	exp;
	char			*ex;

	ex = ft_itoa(exit_code);
	ex_data(&exp);
	exp.i = 0;
	calcul_c(input, &exp, 0, ex);
	exp.result = ft_calloc(ft_strlen(input) + (exp.c * 87) + 1, 1);
	while (input[exp.input_index] != '\0')
	{
		calcul_c(input, &exp, 1, ex);
		if (check_inp(input, exp))
		{
			inist_to_zero(&exp, 0, input);
			if (input[exp.input_index + 1] == '?')
				calcul_c(input, &exp, 2, ex);
			else
				idont_know_what_mdoin(&exp, 0, input, my_env);
		}
		else if (input[exp.input_index] != '\0')
			inist_to_zero(&exp, 1, input);
	}
	free(input);
	free(ex);
	return (exp.result);
}
