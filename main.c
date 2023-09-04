#include <stdio.h>
#include "libft.h"
#include <string.h>

int main(int argc, char *argv[])
{
	/*if (argc != 0)
	{
		ft_bzero(argv[1], 7);
		printf("%s", argv[1]);
	}*/
	if (argc != 0)
	{
		int arr[10];
		ft_memcpy(argv[1], arr, 6);
		unsigned long i = 0;
		while (i < strlen(argv[1]))
		{
			printf ("%d", argv[1][i]);
			i++;
		}
	}
	return 0;
}