/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:07:26 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 08:08:50 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_isascii(int c) {
    if (c >= 0 && c <= 127)
        return (1);
    return (0);
}

int ft_isprint(int c) {
    if (c >= 32 && c <= 126)
        return (1);
    return (0);
}

int ft_isalpha(int c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int ft_isdigit(int c) {
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_isalnum(int c) {
    return (ft_isalpha(c) || ft_isdigit(c));
}

int ft_toupper(int c) {
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

int ft_tolower(int c) {
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}
