/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:45:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/04 17:00:11 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(char *s, int x, unsigned long long n)
{
	unsigned long long	i;

	i = 0;
	while (i < n)
	{
		s[i] = x;
		i++;
	}
	return (0);
}