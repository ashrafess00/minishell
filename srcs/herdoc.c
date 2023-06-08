/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:45:20 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/08 16:57:15 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input_from_fd0(int fd)
{
	char	*buffer;
	char	*input;

	input = ft_calloc(1, 1);
	buffer = get_next_line(fd);
	while (buffer)
	{
		input = ft_strjoin(input, buffer);
		buffer = get_next_line(fd);
	}
	return (input);
}

void	write_input_to_fd1(int fds[2], char *limiter, t_my_env *my_env)
{
	char	*input;
	char	*s;

	signal(SIGINT, SIG_DFL);
	close(fds[0]);
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
	write(fds[1], input, ft_strlen(input));
	close(fds[1]);
	free(s);
	free(input);
	exit(0);
}

char	*get_input_from_usr(char *limiter, t_my_env *my_env)
{
	char	*input;
	int		pid;
	int		fds[2];
	int		status;

	input = ft_calloc(1, 1);
	signal(SIGINT, SIG_IGN);
	pipe(fds);
	pid = fork();
	if (pid == 0)
		write_input_to_fd1(fds, limiter, my_env);
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, ctrl_c_handler);
		close(fds[1]);
		if (WIFSIGNALED(status))
			write(1, "\n", 1);
		free(input);
		input = get_input_from_fd0(fds[0]);
		close(fds[0]);
		return (input);
	}
	return (NULL);
}
