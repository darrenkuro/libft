/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:47:37 by dlu               #+#    #+#             */
/*   Updated: 2023/04/21 11:39:28 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_split_count(char const *s, char c)
{
	int		count;
	int		len;
	char	*trimmed;
	char	sep[2];

	sep[0] = c;
	sep[1] = '\0';
	trimmed = ft_strtrim(s, sep);
	count = 1;
	if (!trimmed)
		return (count);
	len = 0;
	while (*trimmed)
	{
		if (*trimmed != c)
			++len;
		else if (len && *trimmed == c && ++count)
			len = 0;
		++trimmed;
	}
	free(trimmed);
	return (++count);
}
/*
char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		len;
	int		i;
	char	*trimmed;
	char	sep[2];

	if (!s)
		return (NULL);
	ret = (char **) malloc(ft_split_count(s, c) * sizeof(char *));
	if (!ret)
		return (NULL);
	sep[0] = c;
	sep[1] = '\0';
	len = 0;
	i = -1;
	trimmed = ft_strtrim(s, sep);
	while (trimmed[++i])
	{
		if (trimmed[i] != c)
			++len;
		//else if (len && trimmed[i] == c)
			*ret++ = ft_substr(&trimmed[i], 0, len);
	}
	*ret++ = ft_substr(&trimmed[i - len], 0, len);
	*ret = NULL;
	free(trimmed);
	return (ret - ft_split_count(s, c) + 1);
}
*/
#include <stdio.h>
int	main(void)
{
	
	printf("%d\n", ft_split_count("test a", ' '));
	return (0);
}

