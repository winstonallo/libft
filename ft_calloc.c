/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:02:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 12:45:58 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*dest;
	size_t			i;

	dest = malloc(nmemb * size);
	i = 0;
	while (i < nmemb)
	{
		dest[i] = 0;
		i++;
	}
	return ((void *)dest);
}
