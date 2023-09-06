/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:13:53 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 14:43:41 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_set(char c, const char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		counter;
	char	*dest;
	int		j;

	j = 0;
	counter = 0;
	i = -1;
	while (s1[++i])
	{
		if (ft_is_set(s1[i], set) == 0)
			counter++;
	}
	dest = malloc((counter + 1) * sizeof(char));
	i = -1;
	while (s1[++i])
	{
		if (ft_is_set(s1[i], set) == 0)
		{
			dest[j] = s1[i];
			j++;
		}
	}
	return (dest);
}
