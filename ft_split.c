/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:07:49 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 13:47:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c || *(s + 1) == '\0')
			i++;
		s++;
	}
	return (i);
}

int	ft_word_length(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_get_next_word(const char *s, int c)
{
	int		word_length;
	char	*str;
	int		i;

	i = 0;
	word_length = ft_word_length(s, c);
	str = malloc((word_length + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	while (i < word_length)
	{
		str[i] = *s;
		s++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	while (*s)
	{
		arr[i] = ft_get_next_word(s, c);
		if (ft_word_length(s, c) == 0)
			return (arr);
		arr[i][ft_word_length(s, c) + 1] = '\0';
		s += ft_word_length(s, c) + 1;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
