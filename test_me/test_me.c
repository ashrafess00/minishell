#include "test_header.h"
int next_doubl(char *line, int i, char c)
{
    while(line[i])
    {
        if(line[i] == c)
            return(i);
        i++;
    }
    return(0);
}
int strln(char *line)
{
    int i = 0;
    while(line[i])
        i++;
    return(i);
}
char *closed_quote(char *line)
{
    int single = 0;
    int dble = 0;
    int d_po = next_doubl(line, 0, '"');
    int n_do;
    int i = 0;
    int j = 0;
    char *line2;
    line2 =  malloc(strln(line) * sizeof(char *));
    while(line[i])
    {
        if(i > n_do)
        {
            d_po = next_doubl(line, n_do + 1, '"');
            n_do = next_doubl(line, d_po + 1, '"');
        }
        while(line[i] == 39 && (i > n_do || i < d_po))
        {
            i++;
            single++;
        }
        while(line[i] == '"')
        {
            dble++;
            i++;
        }
        line2[j] = line[i];
        i++;
        j++;
    }
    line2[j] = '\0';
    if(dble % 2 != 0)
        return NULL;
    if(single % 2 != 0)
        return NULL;
    return (line2);
}

int main()
{
	printf("%s", closed_quote("'a's\"hr\"af"));
}