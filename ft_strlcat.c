/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:33:17 by dlu               #+#    #+#             */
/*   Updated: 2023/04/17 02:38:05 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	dlen = 0;
	slen = ft_strlen(src);
	while (*dst && dstsize > 0)
	{
		dlen++;
		dst++;
		dstsize--;
	}
	if (!src || dstsize == 0)
		return (dlen + slen);
	while (*src && dstsize > 1)
	{
		*dst = *src;
		src++;
		dst++;
		dstsize--;
	}
	*dst = '\0';
	return (dlen + slen);
}
