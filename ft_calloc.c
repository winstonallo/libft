/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:02:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 14:35:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	size_t			i;

	if (nmemb * size == 0)
		return (0);
	if ((nmemb * size) / size != nmemb)
		return (0);
	dest = malloc(nmemb * size);
	if (dest == NULL)
		return (0);
	i = 0;
	while (i < nmemb)
	{
		dest[i] = 0;
		i++;
	}
	return ((void *)dest);
}
