/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:38:22 by kslik             #+#    #+#             */
/*   Updated: 2023/04/10 01:31:34 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include "libft.h"
# define S_QUOTE '\''
# define D_QUOTE '\"'

typedef struct s_token
{
	int 		num;
	struct s_token	*next;
	struct s_token *prev;
}	t_token;

void	cr_token(t_token **head, int c);
void	lets_parse(char *line);

#endif
