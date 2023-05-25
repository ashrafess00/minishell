/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:58:16 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/25 13:09:21 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s, char *limiter)
{
	int	i;
	int	s_len;
	int	limiter_len;

	s_len = ft_strlen(s);
	limiter_len = ft_strlen(limiter);
	i = 0;
	while (s[i] || limiter[i])
	{
		if (limiter[i] == '\0' && s[i] == '\n')
			return (0);
		if (limiter[i] != s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*get_input_from_usr(char *limiter, t_my_env *my_env)
{
	char	*input;
	char	*s;

	input = ft_calloc(1, 1);
	while (1)
	{
		ft_printf("> ");
		s = get_next_line(0);
		if (s)
			s = expandini(s, my_env, 0);
		if (!s)
			break ;
		if (!ft_strcmp(s, limiter))
			break ;
		input = ft_strjoin(input, s);
	}
	free(s);
	return (input);
}

char	*get_cdir(int exit_code)
{
	char	s[100];
	int		i;
	int		l_i;
	char	*our_shell;

	(void) exit_code;
	getcwd(s, sizeof(s));
	i = -1;
	l_i = 0;
	while (s[++i])
	{
		if (s[i] == '/')
			l_i = i;
	}
	our_shell = ft_strjoin(ft_strdup("\e[1;32m("), ft_strdup(s + l_i));
	if (!exit_code)
		our_shell = ft_strjoin(our_shell, ft_strdup(")😋~> \e[0;37m"));
	else
		our_shell = ft_strjoin(our_shell, ft_strdup(")😋~> \e[0;37m"));
	our_shell = ft_strjoin(ft_strdup("\e[0;31m/our@shell~:"), our_shell);
	return (our_shell);
}

int	is_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '\n'
			&& input[i] != '\t' && input[i] != '\f'
			&& input[i] != '\v' && input[i] != '\r')
			return (0);
	}
	return (1);
}

int	is_single_cmd(t_tree *tree)
{
	if (tree->type == PIPE_NODE)
		return (0);
	else
		return (1);
}
