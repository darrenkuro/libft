/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:37:02 by dlu               #+#    #+#             */
/*   Updated: 2023/04/21 01:51:40 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

/* ////
#include <fcntl.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac < 2 && printf("need 2 args!"))
		return (1);
	int fd = open(av[1], O_RDWR | O_APPEND);
	// by default to the beginning, more flags can be set with bitmask
	ft_putstr_fd("", fd);
	close(fd);
	return (0);
}
*/ ////
