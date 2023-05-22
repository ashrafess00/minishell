/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_me2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:18:33 by kslik             #+#    #+#             */
/*   Updated: 2023/05/22 12:22:33 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ex_data(struct s_expand *exp)
{
	exp->i = 0;
	exp->c = 0;
	exp->resultIndex = 0;
	exp->fl = 0;
	exp->inputIndex = 0;
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
	{
		exp->fl = 0;
		if (exp->inputIndex > 0)
		{
			if (input[exp->inputIndex - 1] == 39)
				exp->fl = 1;
		}
	}
	else if (c == 2)
	{
		while (ex[exp->c])
			exp->result[exp->resultIndex++] = ex[exp->c++];
		exp->inputIndex += 2;
	}
}
