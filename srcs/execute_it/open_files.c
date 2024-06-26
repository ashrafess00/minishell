/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:16:35 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/25 13:15:44 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_outfile(char *file)
{
	int			fd;

	if (is_a_directory(file))
		write_error(file, IS_A_DIRECTORY, STATUS_126);
	if (!access (file, F_OK) && access (file, W_OK))
		write_error(file, PERMISSION_MSG, STATUS_1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		write_error(file, FILE_NOT_FOUND_MSG, 1);
	return (fd);
}

int	open_infile(char *file)
{
	int	fd;

	if (access(file, F_OK))
		write_error(file, FILE_NOT_FOUND_MSG, STATUS_1);
	if (access (file, R_OK))
		write_error(file, PERMISSION_MSG, STATUS_1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		write_error(NULL, "An Error Occured", EXIT_FAILURE);
	return (fd);
}

int	open_outfile_append(char *file)
{
	int	fd;

	if (is_a_directory(file))
		write_error(file, IS_A_DIRECTORY, STATUS_126);
	if (!access (file, F_OK) && access (file, W_OK))
		write_error(file, PERMISSION_MSG, STATUS_1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		write_error(file, FILE_NOT_FOUND_MSG, 1);
	return (fd);
}
