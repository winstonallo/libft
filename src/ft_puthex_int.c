/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:03:09 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/08 16:40:37 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*create_string(unsigned int n, int *strlen)
{
	int				i;
	unsigned int	temp;
	char			*str;

	i = 0;
	temp = n;
	while (temp != 0)
	{
		temp /= 16;
		i++;
	}
	str = ft_calloc(i + 1, sizeof(char));
	*strlen = i - 1;
	return (str);
}

int	ft_puthex_int(int n, int font)
{
	unsigned int	temp;
	char			*str;
	int				i;
	int				*i_ptr;

	i_ptr = &i;
	temp = n;
	str = create_string(n, i_ptr);
	if (!str)
		return (0);
	while (temp != 0)
	{
		if ((temp % 16) < 10)
			str[i] = (temp % 16) + '0';
		else
			str[i] = (temp % 16) + font;
		temp = temp / 16;
		i--;
	}
	ft_putstr_fd(str, 1);
	i = ft_strlen(str);
	free(str);
	if (n == 0)
		i += ft_putchar_int('0');
	return (i);
}
