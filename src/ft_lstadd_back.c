/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:34:49 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 10:10:14 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}
