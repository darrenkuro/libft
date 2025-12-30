/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:32:28 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 10:05:45 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <stddef.h> // size_t

#define DEC "0123456789"
#define HEXU "0123456789ABCDEF"
#define HEXL "0123456789abcdef"

#define NULL_STR "(null)"
#define NULL_PTR "(nil)"

/* clang-format off */
typedef enum e_mode {
    MODE_FD,
    MODE_BUF
} t_mode;

typedef struct s_format
{
	long long	nbr;
	char	type;
	char	padding;
	char	*num;
	int		hash;
	int		minus;
	int		plus;
	int		space;
	int		dot;
	int		zero;
	int		width;
	int		precision;
	int		base;
	int		signed_nbr;
    t_mode  mode;
    int     fd;
    char    *buf;
    size_t  buf_size;
    size_t  buf_pos;
}	t_format;

int ft_printf(const char *s, ...);
int	ft_dprintf(int fd, const char *s, ...);
int ft_snprintf(char *buf, size_t size, const char *s, ...);
int ft_vsnprintf(char *buf, size_t size, const char *s, va_list args);
int ft_asprintf(char **out, const char *s, ...);
int ft_vasprintf(char **out, const char *s, va_list args);

#endif
