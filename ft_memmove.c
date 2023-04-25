/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:31:19 by dlu               #+#    #+#             */
/*   Updated: 2023/04/25 23:57:38 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
		while (len--)
			((char *) dst)[len] = ((char *) src)[len];
	else
		while (++i < len)
			((char *) dst)[i - 1] = ((char *) src)[i - 1];
	return (dst);
}
