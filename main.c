#include <stdio.h>
#include "libft.h"
#include <string.h>
#include <ctype.h>

size_t strlcpy(char       *dst,        /* O - Destination string */
              const char *src,      /* I - Source string */
          size_t      size)     /* I - Size of destination string buffer */
{
  size_t    srclen;         /* Length of source string */


 /*
  * Figure out how much room is needed...
  */

  size --;

  srclen = strlen(src);

 /*
  * Copy the appropriate amount...
  */

  if (srclen > size)
    srclen = size;

  memcpy(dst, src, srclen);
  dst[srclen] = '\0';

  return (srclen);
}

size_t strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
    unsigned long d_len,s_len,offset,src_index;

    /* obtain initial sizes */
    d_len = strlen(dst);
    s_len = strlen(src);

    /* get the end of dst */
    offset = d_len;

    /* append src */
    src_index = 0;
    while( *(src+src_index) != '\0' )
    {
        *(dst+offset) = *(src+src_index);
        offset++;
        src_index++;
        /* don't copy more than dstsize characters
           minus one */
        if( offset==dstsize-1)
            break;
    }
    /* always cap the string! */
    *(dst+offset) = '\0';

    return( d_len+s_len );
}

int main(int argc, char *argv[])
{
	/*if (argc != 0)
	{
		ft_bzero(argv[1], 7);
		printf("%s", argv[1]);
	}*/
	if (argc != 0)
	{
		printf("%d\n", ft_atoi(argv[1]));
		printf("%d\n", atoi(argv[1]));
	}

	return 0;
}