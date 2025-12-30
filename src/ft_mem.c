/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:10:02 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 09:41:43 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h> // MAX_SIZE
#include <stdlib.h> // malloc

void *ft_memset(void *b, int c, size_t len) {
    size_t i;

    i = 0;
    while (i < len)
        ((unsigned char *)b)[i++] = c;
    return (b);
}

void *ft_memmove(void *dst, const void *src, size_t len) {
    size_t i;

    i = 0;
    if (!dst && !src)
        return (NULL);
    if (src < dst)
        while (len--)
            ((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
    else
        while (++i <= len)
            ((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
    return (dst);
}

void *ft_memcpy(void *dst, const void *src, size_t n) {
    size_t i;

    i = 0;
    if (!dst && !src)
        return (NULL);
    while (++i <= n)
        *(unsigned char *)dst++ = *(unsigned char *)src++;
    return (dst - i + 1);
}

int ft_memcmp(const void *s1, const void *s2, size_t n) {
    while (n > 0 && n--)
        if (*(unsigned char *)s1++ != *(unsigned char *)s2++)
            return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
    if (n == 0)
        return (0);
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void *ft_memchr(const void *s, int c, size_t n) {
    size_t i;

    i = 0;
    while (++i <= n)
        if (((unsigned char *)s)[i - 1] == (unsigned char)c)
            return ((void *)&s[i - 1]);
    return (NULL);
}

void ft_bzero(void *s, size_t n) {
    ft_memset(s, 0, n);
}

void *ft_calloc(size_t count, size_t size) {
    void *ret;

    if (size != 0 && count > SIZE_MAX / size)
        return (NULL);
    ret = malloc(count * size);
    if (!ret)
        return (NULL);
    ft_bzero(ret, count * size);
    return (ret);
}
