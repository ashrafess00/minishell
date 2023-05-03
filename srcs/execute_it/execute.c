/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/03 17:01:55 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*search_for_path(char **env, char *command)
{
	char *path_demo = ft_strdup("/usr/bin/sort");
	return (path_demo);
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

int	open_infile(char *file1)
{
	int	fd;

	if (access(file1, F_OK))
		write_error(file1, FILE_NOT_FOUND_MSG, STATUS_1);
	if (access (file1, R_OK))
		write_error(file1, PERMISSION_MSG, STATUS_1);
	fd = open(file1, O_RDONLY);
	if (fd < 0)
		write_error(NULL, "An Error Occured", EXIT_FAILURE);
	return (fd);
}

int	open_outfile(char *file2)
{
	int	fd;

	if (!access (file2, F_OK) && access (file2, W_OK))
		write_error(file2, PERMISSION_MSG, STATUS_1);
	fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		write_error(NULL, "An Error Occured", EXIT_FAILURE);
	return (fd);
}

void	close_fds(int fds[8], int fds_count, ...)
{
	va_list list;
	int     current_fd;
	int     i;

	va_start(list, fds_count);
	current_fd = va_arg(list, int);
	i = -1;
	while (++i < fds_count)
	{
		if (i != current_fd)
			close(fds[i]);
		else
			current_fd = va_arg(list, int);
	}
	va_end(list);
}

void	close_fds_from_parent(int *fds, int fds_count, int fd_i)
{
	int	i;

	i = -1;
	while (++i < fds_count)
	{
		if (i == fd_i * 2)
		{
			close(fds[i + 1]);
			return ;
		}
		close(fds[i]);
	}
}

void	lets_execute(t_tree *tree, char **env, int *fds, int fds_count, int *count)
{
	char	*path;
	char	**paths;
	int		w_to;
	int		r_from;

	if (tree->type == PIPE_NODE)
	{
		lets_execute(tree->left, env, fds, fds_count, count);
		*count += 1;
		lets_execute(tree->right, env, fds, fds_count, count);
	}
	else
	{
		int f = fork();
		if (f == 0)
		{
			if (*count == 0)
			{
				close_fds(fds, fds_count, 1);
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
			}
			else if (*count == fds_count / 2)
			{
				close_fds(fds, fds_count, fds_count - 2);
				dup2(fds[fds_count - 2], STDIN_FILENO);
				close(fds[fds_count - 2]);
			}
			else
			{
				r_from = (*count - 1) * 2;
				w_to = *count * 2 + 1;
				close_fds(fds, fds_count, r_from, w_to);
				dup2(fds[r_from], STDIN_FILENO);
				close(fds[r_from]);
				dup2(fds[w_to], STDOUT_FILENO);
				close(fds[w_to]);
			}
			paths = get_path_from_env(env);
			path = get_path(tree->cmd_node->args[0], paths);
			while (tree->cmd_node->redir_list)
			{
				if (tree->cmd_node->redir_list->type == RED_OUTPUT)
				{
					int fd = open_outfile(tree->cmd_node->redir_list->file_name);
					dup2(fd, STDOUT_FILENO);
				}
				tree->cmd_node->redir_list = tree->cmd_node->redir_list->next;
			}
			execve(path, tree->cmd_node->args, env);
		}
		else
		{
			
			close_fds_from_parent(fds, fds_count, *count);
			wait(NULL);
			return;
		}
	}
}