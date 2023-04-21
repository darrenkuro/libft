/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@42berlin.de>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 06:44:27 by dlu               #+#    #+#             */
/*   Updated: 2023/04/21 07:03:09 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	int	len;

	if (lst)
	{
		len = ft_lstsize(*lst);
		if (!len)
		{
			*lst = new;
			return ;
		}
		while (--len > 0)
			*lst = (*lst)->next;
		(*lst)->next = new;
	}
}
