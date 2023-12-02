/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:25:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/24 13:37:09 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *st_sto, char *buf)
{
	char	*dest;
	int		j;
	int		i;

	i = -1;
	j = 0;
	if (!st_sto)
	{
		st_sto = malloc(1 * sizeof(char));
		if (!st_sto)
			return (NULL);
		st_sto[0] = '\0';
	}
	if (!st_sto || !buf)
		return (NULL);
	dest = malloc((ft_strlen(st_sto) + ft_strlen(buf) + 1) * sizeof(char));
	if (!dest)
		return (free(st_sto), NULL);
	while (st_sto[++i])
		dest[i] = st_sto[i];
	while (buf[j])
		dest[i++] = buf[j++];
	dest[ft_strlen(st_sto) + ft_strlen(buf)] = '\0';
	return (dest);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
