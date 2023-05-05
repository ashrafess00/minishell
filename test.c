#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>


int error_pipe(char *line)
{
    int i = 0;
	int x = 0;
    while(line[i])
    {
		x = 0;
        if(line[i] == '|' && i == 0)
            return(0);
        if((line[i] != '|' || line[i] != '<' || line[i] != '>') && line[i])
            i++;
        if((line[i] == '|' || line[i] == '<' || line[i] == '>') && line[i + 1] == '\0' && i > 0)
            return(0);
		if(line[i] == '|' && line[i + 1] == '|')
			return(0);
		while(line[i] == '>' || line[i] == '<')
		{
			i++;
			x++;
		}
		if(x > 2)
			return(0);
        i++;
    }
    return(1);
}
int main() {
    char *input;
    input = readline("ktb :");
    printf("%d", error_pipe(input));
    return 0;
}