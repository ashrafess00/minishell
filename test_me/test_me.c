#include "test_header.h"


void	new_dl(t_token **head, int c)
{
	t_token *new_dl = malloc(sizeof(t_token));
	t_token *last = *head;
	new_dl->num = c;
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

int main()
{
	t_token	*dl;
	dl = NULL;
	new_dl(&dl, 10);
	new_dl(&dl, 20);
	new_dl(&dl, 30);
	new_dl(&dl, 10);
	new_dl(&dl, 20);
	new_dl(&dl, 30);

	while (dl)
	{
		printf("%d - add %p - next add %p - prev add %p\n", dl->num, dl, dl->next, dl->prev);
		dl = dl->next;
	}


}