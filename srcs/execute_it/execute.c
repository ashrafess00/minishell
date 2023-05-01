/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:33:18 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/01 15:28:07 by aessaoud         ###   ########.fr       */
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

void	lets_execute(t_tree *tree, char **env)
{
	char	*path;
	char	**paths;
	int		fds[2];
	int		f;
	if (tree->type == PIPE_NODE)
	{
		lets_execute(tree->left, env);
		lets_execute(tree->right, env);
	}
	else
	{
		int f = fork();
		if (f == 0)
		{
			// if (tree->cmd_node->cmd_count == 0)
			// {
			// 	close(fds[0]);
			// 	dup2(fds[1], STDOUT_FILENO);
			// 	close(fds[1]);
			// }
			// else
			// {
			// 	close(fds[1]);
			// 	char *mam = ft_calloc(100, 1);
			// 	read(fds[0], mam, 100);
			// 	close(fds[0]);
			// 	printf("[[%s]]\n", mam);
			// 	// dup2(fds[0], STDIN_FILENO);
			// 	// close(fds[0]);
			// }
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
			close(fds[0]);
			close(fds[1]);
			wait(NULL);
			// wait(NULL);

		}
	}

	// close(fds[0]);
	// close(fds[1]);
}