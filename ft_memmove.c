/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:01:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/05 16:08:29 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	char	*temp;

	d = (char *)dest;
	s = (char *)src;
	temp = (char *)src;
	ft_memcpy(temp, s, n);
	ft_memcpy(d, temp, n);
	return (dest);
}
