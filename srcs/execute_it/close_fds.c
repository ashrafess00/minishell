/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:05:11 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/03 18:05:28 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//close file discriptors except the one i give
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

//to close file discriptors which were are not used, from parent process
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