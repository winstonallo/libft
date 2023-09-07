/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:06:23 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/07 11:32:00 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (c > 256)
		c -= 256;
	while (s[i])
	{
		if (s[i] == c)
			j = i;
		i++;
	}
	printf("%d\n", j);
	if (*s == c && c == 0)
		return ((char *)s);
	if (j == -1 && c == 0)
		return ((char *)s + ft_strlen(s));
	if (j == -1)
		return (0);
	return ((char *)s + j);
}
