/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:45:57 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 11:05:43 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	x;

	x = 0;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (0);
	while (x < len && s[start] != '\0')
	{
		dest[x] = s[start];
		x++;
		start++;
	}
	dest[x] = '\0';
	return (dest);
}