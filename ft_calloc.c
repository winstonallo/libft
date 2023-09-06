/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:02:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 19:45:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	dest = NULL;
	if (nmemb == 0 || size == 0)
		return (NULL);
	if ((size * nmemb) / nmemb != size)
		return (NULL);
	dest = malloc(nmemb * size);
	if (dest)
		ft_bzero(dest, size * nmemb);
	return (dest);
}
