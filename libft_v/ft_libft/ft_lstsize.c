/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:15:39 by aessaoud          #+#    #+#             */
/*   Updated: 2022/12/23 14:51:23 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

// int main()
// {
// 	t_list *head;
// 	head = ft_lstnew("headoo");
// 	head->next = ft_lstnew("secendo");
// 	head->next->next = ft_lstnew("thirdo");
// 	head->next->next->next = ft_lstnew("fourtho");
// 	ft_lstadd_front(&head, ft_lstnew("frontooo"));
// 	printf("%d\n", ft_lstsize(head));
// 	printf("%s", head->content);
// }
