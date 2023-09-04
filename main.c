#include <stdio.h>
#include "libft.h"
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	/*if (argc != 0)
	{
		ft_bzero(argv[1], 7);
		printf("%s", argv[1]);
	}*/
	if (argc != 0)
	{
		size_t i = 6;
		printf("%p\n", ft_memmove(argv[1], "arthur", i));
		printf("%p\n", memmove(argv[1], "arthur", i));
	}
	return 0;
}