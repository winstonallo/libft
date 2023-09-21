/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:50:32 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 14:10:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	size;
	size_t	s1_len;
	int		i;

	i = -1;
	s1_len = ft_strlen(s1);
	size = s1_len + ft_strlen(s2) + 1;
	dest = malloc(size * sizeof(char));
	if (dest == NULL)
		return (0);
	while (s1[++i])
		dest[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		dest[s1_len] = s2[i];
		s1_len++;
	}
	dest[s1_len] = '\0';
	return (dest);
}
