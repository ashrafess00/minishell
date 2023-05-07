/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/07 14:45:23 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_echo(char **args)
{
	int	i;

	i = 0;
	if (!args[1])
		return ;
	if (!ft_strcmp(args[1], "-n"))
		i = 1;
	while (args[++i])
	{
		if (args[i + 1])
			printf("%s ", args[i]);
		else
			printf("%s", args[i]);
	}
	if (ft_strcmp(args[1], "-n"))
		printf("\n");
}

void	my_cd(char **args)
{
	if (!args[1])
		return ;
	if (chdir(args[1]))
	{
		write(2, "our@shell: cd: ", 11);
		perror(args[1]);
	}
}

void	my_exit()
{
	exit(0);
}

void	my_pwd()
{
	char	*pwd;

	pwd = getenv("PWD");
	printf("%s\n", pwd);
}

void	is_build_in(char **args)
{
	if (!ft_strcmp(args, "cd"))
		my_cd(args);
	else if (!ft_strcmp(args, "echo"))
		my_echo(args);
	else if (!ft_strcmp(args, "exit"))
		my_exit();
	else if (!ft_strcmp(args, "pwd"))
		my_pwd();
}