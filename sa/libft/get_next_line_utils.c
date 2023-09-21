/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:25:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/21 15:08:10 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *st_sto, char *buf)
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
	dest = malloc((ft_strlen_gnl(st_sto) + ft_strlen_gnl(buf) + 1));
	if (!dest)
		return (free(st_sto), NULL);
	while (st_sto[++i])
		dest[i] = st_sto[i];
	while (buf[j])
		dest[i++] = buf[j++];
	dest[ft_strlen_gnl(st_sto) + ft_strlen_gnl(buf)] = '\0';
	free(st_sto);
	return (dest);
}

char	*ft_strchr_gnl(char *s, int c)
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
