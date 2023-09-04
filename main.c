#include <stdio.h>
#include "libft.h"

int main(int argc, char *argv[])
{
	if (argc != 0)
		printf("%d", ft_strlen(argv[1]));
	return 0;
}