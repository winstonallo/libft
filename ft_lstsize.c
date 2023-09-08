/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:43:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/08 14:30:07 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int			i;
	t_list		*current;

	i = 0;
	current = lst;
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	if (!current->next)
		i++;
	return (i);
}