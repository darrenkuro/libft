/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 03:42:50 by dlu               #+#    #+#             */
/*   Updated: 2023/04/21 01:10:28 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#define INT_MIN -2147483648
#define INT_MIN_LEN 12
#define BASE 10

/* Return the length of itoa string, including the '\0'. */
static size_t	ft_itoa_len(int n)
{
	size_t	len;

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

char	*ft_itoa(int n)
{
	char	*num;
	size_t	len;

	len = ft_itoa_len(n);
	num = (char *) malloc(len * sizeof(char));
	if (!num)
		return (NULL);
	if (n < 0)
		num[0] = '-';
	num[--len] = '\0';
	while (--len >= 0 && num[len] != '-')
	{
		if (n > 0)
			num[len] = n % BASE + '0';
		else
			num[len] = -(n % BASE) + '0';
		n /= BASE;
	}
	return (num);
}

/* ////
#include <stdio.h>
int	main()
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(-8));
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(2579));
	return (0);
}
*/ ////
