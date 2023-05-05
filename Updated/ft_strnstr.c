/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:13:21 by dlu               #+#    #+#             */
/*   Updated: 2023/04/21 09:50:23 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *) haystack);
	while (i < len && haystack[i])
	{
		while ((i + j) < len && haystack[i + j] == needle[j]
			&& haystack[i + j])
			++j;
		if (!needle[j])
			return ((char *) haystack + i);
		j = 0;
		++i;
	}
	return (NULL);
}

/* ////
#include <stdio.h>
#include <string.h>
int	main()
{
	char *s1 = "MZIRIBMZIRIBMZE123";
	char *s2 = "MZIRIBMZE";
	size_t max = strlen(s2);
	char *i1 = strnstr(s1, s2, max);
	char *i2 = ft_strnstr(s1, s2, max);
	printf("%s %s %zu\n", s1, s2, max);
	printf("%s %s\n", i1, i2);
	//printf("%d\n", strcmp(i1, i2));
	return (0);
}
*/ ////
