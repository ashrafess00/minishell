/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:46:37 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/27 18:56:43 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//mn pipex :)

void	write_error(char *file1, char *msg, int exit_status)
{
	char	*pipex_t;

	pipex_t = ft_strdup("/our@shell: ");
	ft_putstr_fd(pipex_t, 2);
	if (file1)
		ft_putstr_fd(file1, 2);
	ft_putstr_fd(msg, 2);
	write(2, "\n", 1);
	free(pipex_t);
	exit(exit_status);
}

char	*get_path(char *program, char **paths)
{
	int		i;
	char	*full_path;

	i = -1;
	if (!program || !*paths)
		return (0);
	if (!access(program, F_OK) && access(program, X_OK | R_OK))
		write_error(program, PERMISSION_MSG, STATUS_126);
	if (!access(program, F_OK | X_OK | R_OK))
		return (program);
	if (program[0] == '/' && access(program, F_OK))
		write_error(program, COMMAND_NOT_FOUND, STATUS_127);
	if (!paths)
		write_error(program, FILE_NOT_FOUND_MSG, STATUS_127);
	while (paths[++i])
	{
		full_path = ft_strjoin(ft_strdup(paths[i]), ft_strdup("/"));
		full_path = ft_strjoin(full_path, ft_strdup(program));
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free (full_path);
	}
	write_error(program, COMMAND_NOT_FOUND, STATUS_127);
	return (NULL);
}
