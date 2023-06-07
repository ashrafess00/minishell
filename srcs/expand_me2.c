/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_me2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:18:33 by kslik             #+#    #+#             */
/*   Updated: 2023/06/07 18:55:27 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	betweensingle(char *input, int index)
{
	int	open_qu;
	int	i;

	open_qu = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (open_qu == 0 && input[i] == '\'')
			open_qu = 1;
		else if (open_qu == 1 && input[i] == '\'')
			open_qu = 0;
		if (i == index)
			return (open_qu);
		i++;
	}
	return (0);
}

void	ex_data(struct s_expand *exp)
{
	exp->i = 0;
	exp->c = 0;
	exp->result_index = 0;
	exp->fl = 0;
	exp->input_index = 0;
	exp->brek = 0;
}

void	calcul_c(char *input, struct s_expand *exp, int c, char *ex)
{
	if (c == 0)
	{
		while (input[exp->i])
		{
			if (input[exp->i] == '$')
				exp->c++;
			exp->i++;
		}
	}
	else if (c == 1)
		exp->fl = betweensingle(input, exp->input_index);
	else if (c == 2)
	{
		while (ex[exp->c])
			exp->result[exp->result_index++] = ex[exp->c++];
		exp->input_index += 2;
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
			if (exp->pedi[exp->i] == '\0' && exp->tmp->val[exp->i] == '=')
			{
				search_key(input, exp, 1);
				exp->brek = 1;
				break ;
			}
			exp->tmp = exp->tmp->next;
		}
	}
}
