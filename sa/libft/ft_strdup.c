/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:58:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/07 18:54:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		size;

	size = ft_strlen(src) + 1;
	dest = (char *)malloc(sizeof(char) * (size));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, size);
	return ((char *)dest);
}
