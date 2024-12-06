/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:21:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/08 16:40:17 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void *
ft_memcpy(void *dest, const void *src, size_t n) {
    if (!dest && !src) {
        return (NULL);
    }

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__)
    __asm__ __volatile__("rep movsb" : : "S"(src), "D"(dest), "c"(n) : "memory");
#else
    size_t i = 0;

    while (i < n) {
        ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
        i++;
    }
#endif

    return dest;
}