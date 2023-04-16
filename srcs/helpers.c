/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:46:01 by aessaoud          #+#    #+#             */
/*   Updated: 2023/04/16 23:33:29 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_tokens(t_token *head)
{
	// t_token *too = head;
	while (head)
	{
		printf("arg : [%-10s]| i : %-5d| size : %-5d| ", head->s, head->s_index, head->size);
		if (head->type == NORMAL)
			printf("TYPE : NORMAL\n");
		if (head->type == ENV)
			printf("TYPE : ENV\n");
		if (head->type == RED_INPUT)
			printf("TYPE : <\n");
		if (head->type == RED_OUTPUT_APPEND)
			printf("TYPE : >>\n");
		if (head->type == RED_OUTPUT)
			printf("TYPE : >\n");
		if (head->type == HEREDOC)
			printf("TYPE : <<\n");
		if (head->type == PIPE)
			printf("TYPE : |\n");
		if (head->type == SPACE)
			printf("TYPE : SPACE\n");
		if (head->type == EXIT_STATUS)
			printf("TYPE : EXIT_CODE\n");
		head = head->next;
	}
}