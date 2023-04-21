/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 03:42:50 by dlu               #+#    #+#             */
/*   Updated: 2023/04/21 06:34:26 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/* Return the length of itoa string, including the '\0'. */
static size_t	ft_itoa_len(int n)
{
	size_t	len;

	len = 1;
	if (n == 0)
		return (++len);
	if (n == -2147483648)
		return (12);
	if (n < 0 && ++len)
		n = -n;
	while (n > 0 && ++len)
		n /= 10;
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
			num[len] = n % 10 + '0';
		else
			num[len] = -(n % 10) + '0';
		n /= 10;
	}
	return (num);
}

/* ////
#include <stdio.h>
#include <string.h>
int	main()
{
	char *abc =ft_itoa(2147483647);

	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-8));
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(-620));
	printf("%d\n", strcmp(ft_itoa(-0), "0"));
	if (atoi(abc) == 2147483647)
		printf("ok!\n");
	return (0);
}
*/ ////
