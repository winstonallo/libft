/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:21:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/04 17:28:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, const void *src, unsigned long long n);
{
	unsigned char		*d = dest;
    const unsigned char	*s = src;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}
