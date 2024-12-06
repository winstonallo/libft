/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:11:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/08 16:40:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int
ft_putstr_int(int fd, char *s) {
    if (!s) {
        ft_putstr_fd("(null)", fd);
        return 6;
    }

    size_t len = ft_strlen(s);

    write(fd, s, len);
    return len;
}
