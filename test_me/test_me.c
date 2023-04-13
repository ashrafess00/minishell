#include "test_header.h"


void	new_dl(t_token **head, int c, enum e_chars	chars)
{
	t_token *new_dl = malloc(sizeof(t_token));
	t_token *last = *head;
	new_dl->num = c;
	new_dl->chars = chars;
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

int	is_pipe(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s[0] == '|')
	{
		count += 1;
		while (s[++i])
		{
			if (s[i] == '|')
				count ++;
			if (count == 2)
			{
				printf("syntax error\n");
				return (0);
			}
			if (s[i] != ' ')
				return (1);
		}
	}
	return (0);
}


int main()
{
	printf("%d", is_pipe("|   \"|hello my name is ashraf"));
	// t_token	*dl;
	// dl = NULL;
	// new_dl(&dl, 10, WORD);
	// new_dl(&dl, 20, WORD);
	// new_dl(&dl, 30, WORD);
	// new_dl(&dl, 10, JI);
	// new_dl(&dl, 20, WORD);
	// new_dl(&dl, 30, WORD);

	// while (dl)
	// {
	// 	printf("%d - add - [%d] - %p - next add %p - prev add %p\n", dl->chars, dl->num, dl, dl->next, dl->prev);
	// 	dl = dl->next;
	// }


}