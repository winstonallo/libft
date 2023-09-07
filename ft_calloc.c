/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:02:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/07 11:07:25 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	dest = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((size * nmemb) / nmemb != size)
		return (NULL);
	dest = malloc(nmemb * size);
	if (dest == NULL)
		return (NULL);
	if (dest)
		ft_bzero(dest, size * nmemb);
	return (dest);
}
