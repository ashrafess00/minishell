/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:14:23 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/08 14:13:28 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tokens(t_token *tokens, int *exit_code)
{
	while (tokens)
	{
		if (!tokens->s || (tokens->type != WORD && !tokens->next)
			|| (tokens->type != WORD && tokens->next->type != WORD))
		{
			ft_putstr_fd("Syntax Error!!\n", 2);
			*exit_code = 258;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
