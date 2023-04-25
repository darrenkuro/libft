/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 05:24:31 by dlu               #+#    #+#             */
/*   Updated: 2023/04/26 01:33:36 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = -1;
	while (dstsize-- > 0 && src[++i])
		dst[i] = src[i];
	if (dstsize)
		dst[i] = '\0';
	return (ft_strlen(src));
}
