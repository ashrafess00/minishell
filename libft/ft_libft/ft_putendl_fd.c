/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:14:07 by aessaoud          #+#    #+#             */
/*   Updated: 2022/12/23 14:51:23 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		write (fd, &s[i], 1);
	write (fd, "\n", 1);
}

// #include <fcntl.h>
// int	main()
// {
// 	int	fd;
// 	fd = open("mytxt3", O_RDWR | O_CREAT);
// 	ft_putendl_fd("", fd);
// 	printf("%d", fd);
// }