#include "libft.h"



int main(int argc, char *argv[])
{
	//ISALPHA
	/*if (argc != 0)
	{
		printf("FT_ISALPHA: %d\n", ft_isalpha(argv[1][0]));
		printf("ISALPHA: %d\n", isalpha(argv[1][0]));
	}
	*/
	//ISDIGIT
	/*if (argc != 0)
	{
		printf("FT_ISDIGIT: %d\n", ft_isdigit(argv[1][0]));
		printf("ISDIGIT: %d\n", isdigit(argv[1][0]));
	}*/
	//ISALNUM
	/*if (argc != 0)
	{
		printf("FT_ISALNUM: %d\n", ft_isalnum(argv[1][0]));
		printf("ISALNUM: %d\n", isalnum(argv[1][0]));
	}*/
	//ISASCII
	/*if (argc != 0)
	{
		printf("FT_ISASCII: %d\n", ft_isascii(argv[1][0]));
		printf("ISASCII: %d\n", isascii(argv[1][0]));
	}*/
	//ISPRINT
	/*if (argc != 0)
	{
		printf("FT_ISPRINT: %d\n", ft_isprint(argv[1][0]));
		printf("ISPRINT: %d\n", isprint(argv[1][0]));
	}*/
	//STRLEN
	/*if (argc != 0)
	{
		printf("FT_STRLEN: %zu\n", ft_strlen(argv[1]));
		printf("STRLEN: %zu\n", strlen(argv[1]));
	}*/
	//MEMSET
	/*if (argc != 0)
	{
		char arr[10];
		char arr1[10];

		strlcpy(arr, argv[1], ft_strlen(argv[1]));
		strlcpy(arr1, argv[1], ft_strlen(argv[1]));
		ft_memset(arr + 3, '$', 7);
		memset(arr1 + 3, '$', 7);
		printf("FT_MEMSET: %s\n", arr);
		printf("MEMSET: %s\n", arr1);
	}*/
	//BZERO
	/*if (argc != 0)
	{
		char arr[20];
		char arr1[20];

		ft_strlcpy(arr, argv[1], ft_strlen(argv[1]));
		ft_strlcpy(arr1, argv[1], ft_strlen(argv[1]));
		ft_bzero(arr + 3, 6);
		bzero(arr1 + 3, 6);
		printf("FT_BZERO: %s\n", arr);
		printf("BZERO: %s\n", arr1);
	}*/
	//MEMCPY
	/*if (argc != 0)
	{
		char arr[20];
		char arr1[20];

		ft_bzero(arr, 20);
		ft_bzero(arr1, 20);
		ft_memcpy(arr, argv[1], 10);
		memcpy(arr1, argv[1], 10);
		printf("FT_MEMCPY: %s\n", arr);
		printf("MEMCPY: %s\n", arr1);
	}*/
	//MEMMOVE
	/*if (argc != 0)
	{
		char arr[20];
		char arr1[20];

		ft_bzero(arr, 20);
		ft_bzero(arr1, 20);
		ft_memmove(arr, argv[1], 20);
		memmove(arr1, argv[1], 20);
		printf("FT_MEMMOVE: %s\n", arr);
		printf("MEMMOVE: %s\n", arr1);
	}*/
	//STRLCPY
	/*if (argc != 0)
	{
		char arr[6];
		char arr1[6];

		ft_bzero(arr, 6);
		ft_bzero(arr1, 6);
		ft_strlcpy(arr, argv[1], 7);
		strlcpy(arr1, argv[1], 7);
		printf("FT_STRLCPY: %s\nLENGTH: %zu\n", arr, ft_strlcpy(arr, argv[1], 6));
		printf("STRLCPY: %s\nLENGTH: %zu\n", arr1, strlcpy(arr, argv[1], 6));
	}*/
	//STRLCAT
	/*if (argc != 0)
	{
		char arr[];
		char arr1[];

		ft_strlcat(arr, argv[1], 10);
		strlcat(arr1, argv[1], 10);
		printf("FT_STRLCAT: %s\nLENGTH: %zu\n", arr, ft_strlcat(arr, argv[1], 6));
		printf("STRLCAT: %s\nLENGTH: %zu\n", arr1, strlcat(arr, argv[1], 6));
	}*/
	//TOUPPER
	/*if (argc != 0)
	{
		printf("FT_TOUPPER: %d\n", ft_toupper(ft_atoi(argv[1])));
		printf("TOUPPER: %d\n", toupper(ft_atoi(argv[1])));
	}*/
	//TOLOWER
	/*if (argc != 0)
	{
		printf("FT_TOLOWER: %d\n", ft_tolower(ft_atoi(argv[1])));
		printf("TOLOWER: %d\n", tolower(ft_atoi(argv[1])));
	}*/
	//STRCHR
	/*if (argc != 0)
	{
		char *arr = argv[1];
		char *arr1 = argv[1];
		printf("FT_STRCHR: %s\n", ft_strchr(arr, 's'));
		printf("STRCHR: %s\n", strchr(arr1, 's'));
	}*/
	//STRRCHR
	/*if (argc != 0)
	{
		char *arr = argv[1];
		char *arr1 = argv[1];
		printf("FT_STRRCHR: %s\n", ft_strrchr(arr, 's'));
		printf("STRRCHR: %s\n", strrchr(arr1, 's'));
	}*/
	//STRNCMP
	/*if (argc != 0)
	{
		char *arr = argv[1];
		char *arr1 = argv[1];
		char *err = argv[2];
		char *err1 = argv[2];
		printf("FT_STRNCMP: %d\n", ft_strncmp(arr, err, 5));
		printf("STRNCMP: %d\n", strncmp(arr1, err1, 5));
	}*/
	//MEMCHR
	/*if (argc != 0)
	{
		char *arr = argv[1];
		char *arr1 = argv[1];
		printf("FT_MEMCHR: %p\n", ft_memchr(arr, 's', 5));
		printf("MEMCHR: %p\n", memchr(arr1, 's', 5));
	}*/
	//MEMCMP
	/*if (argc != 0)
	{
		char *arr = argv[1];
		char *arr1 = argv[1];
		char *err = argv[2];
		char *err1 = argv[2];
		printf("FT_MEMCMP: %d\n", ft_memcmp(arr, err, 5));
		printf("MEMCMP: %d\n", memcmp(arr1, err1, 5));
	}*/
	//STRNSTR
	/*if (argc != 0)
	{
		//char *arr = argv[1];
		//char *arr1 = argv[2];
		char *err = argv[1];
		char *err1 = argv[2];
		printf("FT_STRNSTR: %s\n", ft_strnstr(err, err1, 20));
		printf("STRNSTR: %s\n", strnstr(err, err1, 20));
	}*/
	//ATOI
	/*if(argc != 0)
	{
		printf("FT_ATOI: %d\n", ft_atoi(argv[1]));
		printf("ATOI: %d\n", atoi(argv[1]));	
	}*/
	//STRDUP
	/*if (argc != 0)
	{
		printf("FT_STRDUP: %s\n", ft_strdup(argv[1]));
		printf("STRDUP: %s\n", strdup(argv[1]));
	}*/
	//CALLOC
	/*if (argc != 0 && argv[0])
	{
		char *str = ft_calloc(10, sizeof(int));
		char *str1 = calloc(10, sizeof(int));
		printf("FT_CALLOC: \n");
		for (int i = 0; i < 10; i++)
			printf("%d\n", str[i]);
		printf("CALLOC: \n");
		for (int i = 0; i < 10; i++)
			printf("%d\n", str1[i]);
	}*/
	return (0);
}
