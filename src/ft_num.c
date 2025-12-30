/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 09:29:54 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 09:48:14 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h> // read

#define INT_MIN_LEN 12
#define BASE 10

int ft_atoi(const char *str) {
    int num;
    int neg;

    num = 0;
    neg = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        ++str;
    if (*str == '+')
        ++str;
    else if (*str == '-' && ++str)
        neg = -1;
    while ((*str >= '0' && *str <= '9') && ++str)
        num = num * BASE + (*(str - 1) - '0');
    return (neg * num);
}

/* Return the length of itoa string, including the '\0'. */
static size_t ft_itoa_len(int n) {
    size_t len;

    len = 1;
    if (n == 0)
        return (++len);
    if (n == INT_MIN)
        return (INT_MIN_LEN);
    if (n < 0 && ++len)
        n = -n;
    while (n > 0 && ++len)
        n /= BASE;
    return (len);
}

char *ft_itoa(int n) {
    char *num;
    int len;

    len = (int)ft_itoa_len(n);
    num = malloc(len * sizeof(char));
    if (!num)
        return (NULL);
    if (n < 0)
        num[0] = '-';
    num[--len] = '\0';
    while (--len >= 0 && num[len] != '-') {
        if (n > 0)
            num[len] = n % BASE + '0';
        else
            num[len] = -(n % BASE) + '0';
        n /= BASE;
    }
    return (num);
}
