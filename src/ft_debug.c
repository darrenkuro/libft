/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 21:36:57 by dlu               #+#    #+#             */
/*   Updated: 2025/12/31 22:08:00 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/* Print the binary data of len from the address of ptr. */
void ft_printb(const void *ptr, size_t len) {
    const unsigned char *p = ptr;

    for (size_t i = 0; i < len; i++) {
        for (int bit = 7; bit >= 0; bit--)
            write(1, ((p[i] >> bit) & 1) ? "1" : "0", 1);
        write(1, " ", 1);
    }
    write(1, "\n", 1);
}

/* Print the binary data of len in hex from the address of ptr. */
void ft_printh(const void *ptr, size_t len) {
    const unsigned char *p = ptr;

    for (size_t i = 0; i < len; i++)
        ft_printf("%X%X ", p[i] >> 4, p[i] & 0x0F);
    ft_printf("\n");
}

/* Print the binary data of len in char from the address of ptr. */
void ft_printc(const void *ptr, size_t len) {
    const unsigned char *p = ptr;

    for (size_t i = 0; i < len; i++)
        ft_printf("%c", ft_isprint(p[i]) ? p[i] : '-');
    ft_printf("\n");
}
