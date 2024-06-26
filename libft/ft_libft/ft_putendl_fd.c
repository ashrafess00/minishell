/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:14:07 by aessaoud          #+#    #+#             */
/*   Updated: 2023/06/06 13:57:28 by aessaoud         ###   ########.fr       */
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
