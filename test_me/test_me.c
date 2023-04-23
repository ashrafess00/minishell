#include "test_header.h"

void	add_token(t_token **head, char *s, int s_index, int size, enum e_token type)
{
	t_token	*new_dl;
	t_token	*last;

	if (size == 0)
		return ;
	new_dl = malloc(sizeof(t_token));
	last = *head;
	new_dl->s_index = s_index;
	new_dl->s = ft_substr(s + s_index, 0, size);
	//fl function dyalk siftliha (ft_substr(s + s_index, 0, size)), substr ghadi tjiblik string kif mma hwwa
	new_dl->size = size;
	new_dl->type = type;
	new_dl->next = NULL;
	if (*head == NULL)
	{
		new_dl->prev = NULL;
		*head = new_dl;
	}
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_dl;
		new_dl->prev = last;
	}
}

int main(int c, char **argv)
{

}