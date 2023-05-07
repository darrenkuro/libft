/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:25:04 by dlu               #+#    #+#             */
/*   Updated: 2023/04/22 18:40:36 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
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
	ft_putchar_fd('-', fd);
	close(fd);
	return (0);
}
*/ ////
