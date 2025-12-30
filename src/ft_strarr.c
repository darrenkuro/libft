/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:08:56 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 09:47:27 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h> // NULL
#include <stdlib.h> // free

int ft_strarrlen(char **arr) {
    int i;

    if (!arr)
        return (0);
    i = -1;
    while (arr[++i])
        ;
    return (i);
}

char **ft_strarrcpy(char **arr) {
    char **ret;
    int i;

    ret = malloc(sizeof(char *) * (ft_strarrlen(arr) + 1));
    if (!ret)
        return (NULL);
    i = -1;
    while (arr[++i]) {
        ret[i] = ft_strdup(arr[i]);
        if (!ret[i]) {
            while (--i >= 0)
                free(ret[i]);
            return (free(ret), NULL);
        }
    }
    return (ret);
}
