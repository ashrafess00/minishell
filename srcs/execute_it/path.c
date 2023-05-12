/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:46:37 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 15:34:33 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//mn pipex :)
void	write_error(char *file1, char *msg, int exit_status)
{
	char	*our_shell;

	our_shell = ft_strdup("our@shell: ");
	ft_putstr_fd(our_shell, 2);
	if (file1)
		ft_putstr_fd(file1, 2);
	ft_putstr_fd(msg, 2);
	write(2, "\n", 1);
	free(our_shell);
	exit(exit_status);
}

int	is_a_directory(char *program, char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		if (!ft_strcmp(program, paths[i]))
			return (1);
	}
	return (0);
}

char	*get_path(char *program, char **paths)
{
	int		i;
	char	*full_path;

	i = -1;
	if (!program || !*paths)
		return (0);
	// if (!access(program, F_OK) && access(program, X_OK | R_OK))
	// 	write_error(program, PERMISSION_MSG, STATUS_126);
	// if (!access(program, F_OK | X_OK | R_OK))
	// 	return (program);
	// if (program[0] == '/' && access(program, F_OK))
	// 	write_error(program, FILE_NOT_FOUND_MSG, STATUS_127);
	if (!paths)
		write_error(program, FILE_NOT_FOUND_MSG, STATUS_127);
	if (is_a_directory(program, paths))
		write_error(program, IS_A_DIRECTORY, 126);
	while (paths[++i])
	{
		full_path = ft_strjoin(ft_strdup(paths[i]), ft_strdup("/"));
		full_path = ft_strjoin(full_path, ft_strdup(program));
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free (full_path);
	}
	if (!access(program, F_OK | X_OK | R_OK))
		return (program);
	// if (program[0] == '/' && access(program, F_OK))
	// 	write_error(program, COMMAND_NOT_FOUND, STATUS_127);
	if (!access(program, F_OK) && access(program, X_OK | R_OK))
		write_error(program, PERMISSION_MSG, STATUS_126);
	write_error(program, COMMAND_NOT_FOUND, STATUS_127);
	return (NULL);
}

char	**get_path_from_env(char **env)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = -1;
	if (!*env)
	{
		paths = ft_split(ft_strdup("/usr/bin:/bin:/usr/\
		sbin:/sbin:/usr/local/bin"), ':');
		if (!paths)
			return (0);
		return (paths);
	}
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			paths = ft_split(ft_strdup(env[i]), ':');
			if (paths)
				paths[0] = ft_strtrim(paths[0], "PATH=");
			break ;
		}
	}
	return (paths);
}
