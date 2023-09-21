/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:13:53 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/21 12:56:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s1))
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_end(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s1))
	{
		if (ft_strchr(set, s1[ft_strlen(s1) - i - 1]) == 0)
			break ;
		i++;
	}
	return (ft_strlen(s1) - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		e;
	char	*res;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL || set[0] == '\0')
		return (ft_strdup(s1));
	s = ft_start(s1, set);
	e = ft_end(s1, set);
	if (e - s <= 0)
		return (ft_calloc(1, sizeof(char)));
	res = malloc((e - s + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1 + s, e - s + 1);
	return (res);
}
