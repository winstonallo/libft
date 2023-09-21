/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:07:49 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/14 21:08:09 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
	return (NULL);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	if (!s[0])
		return (0);
	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			j++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		j++;
	return (j);
}

static void	ft_get_next_word(char **word, size_t *word_length, char c)
{
	size_t	i;

	*word += *word_length;
	*word_length = 0;
	i = 0;
	while (**word && **word == c)
		(*word)++;
	while ((*word)[i])
	{
		if ((*word)[i] == c)
			return ;
		(*word_length)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*word;
	size_t	word_length;
	size_t	i;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	word = (char *)s;
	word_length = 0;
	while (i < ft_count_words(s, c))
	{
		ft_get_next_word(&word, &word_length, c);
		arr[i] = malloc((word_length + 1) * sizeof(char));
		if (!arr[i])
			return (ft_free_array(arr));
		ft_strlcpy(arr[i], word, word_length + 1);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
