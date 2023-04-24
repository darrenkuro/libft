/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:38:11 by dlu               #+#    #+#             */
/*   Updated: 2023/04/23 17:33:38 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i++])
		f(i - 1, &s[i - 1]);
}

/* ////
void	ft_striteri_a(unsigned int i, char *s)
{
	if (i < 2)
		*s = 'a';
}

#include <stdio.h>

int	main(void)
{
	char	test[8] = "abcdefg";

	ft_striteri(test, ft_striteri_a);
	printf("%s\n", test);

	return (0);
}
*/ ////
