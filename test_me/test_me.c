#include "test_header.h"

typedef enum e_l
{
	D = '0',
	DD = 'd',
}	t_e;

int main(int c, char **argv)
{
	t_e no;

	no = D;
	printf("%c", no);
	no = DD;
	printf("%c", no);

}