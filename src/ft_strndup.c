/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:53:35 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/16 15:54:34 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (len < maxlen && *s)
		len++;
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t		len;
	char		*new;

	len = ft_strnlen(s, n);
	if (len < n)
		n = len;
	new = (char *) malloc (len + 1);
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	return ((char *) ft_memcpy(new, s, len));
}
