/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:32:28 by dlu               #+#    #+#             */
/*   Updated: 2026/01/01 02:08:13 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <stddef.h> // size_t
#include <stdint.h> // uint32_t

#define NULL_STR "(null)"
#define NULL_PTR "(nil)"

/* clang-format off */
typedef enum {
    MODE_FD,
    MODE_BUF
} t_mode;

enum {
    F_HASH  = 1 << 0,
    F_MINUS = 1 << 1,
    F_PLUS  = 1 << 2,
    F_SPACE = 1 << 3,
    F_ZERO  = 1 << 4,
    F_DOT   = 1 << 5,
    F_SIGN  = 1 << 6,
};

typedef struct s_format
{
	char	    type;       // specifier, i.e. 'x', 'd', 'c', 's'
	char	    padding;    // padding char, ' ' or '0'
	char	    num[128];
	uint32_t    flags;      // bitmask for flags
	uint32_t	base;       // base in number
    int     	width;      // width specified with #
	int     	prec;       // precision specified with '.'

    t_mode      mode;
    uint16_t    fd;
    char        *buf;
    size_t      buf_size;
    size_t      buf_pos;
}	t_format;

#define FLAG_SET(x, f)  ((x->flags) |= (f))
#define FLAG_CLR(x, f)  ((x->flags) &= ~(f))
#define FLAG_HAS(x, f)  ((x->flags) & (f))

int ft_printf(const char *s, ...);
int	ft_dprintf(int fd, const char *s, ...);
int ft_snprintf(char *buf, size_t size, const char *s, ...);
int ft_vsnprintf(char *buf, size_t size, const char *s, va_list args);
int ft_asprintf(char **out, const char *s, ...);
int ft_vasprintf(char **out, const char *s, va_list args);

#endif
