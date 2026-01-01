/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:18 by dlu               #+#    #+#             */
/*   Updated: 2026/01/01 03:01:49 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h> // free, NULL
#include <unistd.h> // write

/* Helper function to replace write so it can write to memory as well. */
static void emit(t_format *f, const char *s, size_t n) {
    if (f->mode == MODE_FD) {
        size_t off = 0;
        while (off < n) {
            ssize_t ret = write(f->fd, s + off, n - off);
            if (ret <= 0)
                break;
            off += (size_t)ret;
        }
    } else {
        size_t i = 0;
        while (i < n && f->buf_pos + 1 < f->buf_size) {
            f->buf[f->buf_pos++] = s[i++];
        }
    }
}

/* Return the length to be printed for a given string. */
size_t ft_strlenf(const char *s, const t_format *f) {
    size_t len = 0;

    if (!s)
        return (0);

    if (f->type == 's' && FLAG_HAS(f, F_DOT)) {
        while (s[len] && len < (size_t)f->prec)
            len++;
        return (len);
    }

    while (s[len])
        len++;

    return (len);
}

/* Print the padding and return the length of the padding printed. */
size_t print_padding(char c, size_t len, t_format *f) {
    for (size_t i = 0; i < len; i++)
        emit(f, &c, 1);
    return len;
}

/* Parse the flags in order. */
static void parse_flags(char **s, t_format *f) {
    while (**s == '#' && (*s)++)
        FLAG_SET(f, F_HASH);
    while (**s == '-' && (*s)++)
        FLAG_SET(f, F_MINUS);
    while (**s == '+' && (*s)++)
        FLAG_SET(f, F_PLUS);
    while (**s == ' ' && (*s)++)
        FLAG_SET(f, F_SPACE);
    while (**s == '0' && (*s)++)
        FLAG_SET(f, F_ZERO);
    if (FLAG_HAS(f, F_PLUS))
        FLAG_CLR(f, F_SPACE);
    if (FLAG_HAS(f, F_MINUS))
        FLAG_CLR(f, F_ZERO);
}

/* Parse the width of the format. */
static void parse_width(char **s, va_list *args, t_format *f) {
    if (**s == '*') {
        f->width = va_arg(*args, int);
        (*s)++;
        return;
    }
    while (**s >= '0' && **s <= '9') {
        f->width = (f->width * 10) + **s - '0';
        (*s)++;
    }
}

/* Parse the precision of the format. */
static void parse_precision(char **s, va_list *args, t_format *f) {
    if (**s == '.') {
        FLAG_SET(f, F_DOT);
        (*s)++;
    }
    if (**s == '*') {
        f->prec = va_arg(*args, int);
        if (f->prec < 0)
            f->prec = 0;
        (*s)++;
        return;
    }
    while (**s >= '0' && **s <= '9') {
        f->prec = (f->prec * 10) + **s - '0';
        (*s)++;
    }
}

/* Parse the format and set its parameters. */
void parse_format(char **s, va_list *args, t_format *f) {
    parse_flags(s, f);
    parse_width(s, args, f);
    parse_precision(s, args, f);
    f->type = **s;
    if (ft_strchr("pxXm", **s))
        f->base = 16;
    if (ft_strchr("b", **s))
        f->base = 2;
    if (ft_strchr("di", **s))
        FLAG_SET(f, F_SIGN);
    if (FLAG_HAS(f, F_ZERO))
        f->padding = '0';
    if (FLAG_HAS(f, F_DOT) && FLAG_HAS(f, F_ZERO))
        f->padding = ' ';
    (*s)++;
}

/* Return the length of the nbr string, excluding '\0'. */
static size_t nbr_strlen(long long n, t_format *f) {
    size_t flen = 0, nlen = 0;

    /* calculate format adjustment for nbr length */
    if (FLAG_HAS(f, F_DOT) && !f->prec && n == 0)
        return (0);
    if (FLAG_HAS(f, F_SIGN) && (n < 0 || FLAG_HAS(f, F_PLUS) || FLAG_HAS(f, F_SPACE)))
        flen += 1;
    if ((((ft_strchr("xX", f->type)) && FLAG_HAS(f, F_HASH)) || f->type == 'p') && n != 0)
        flen += 2;

    /* calculate length of the number portion */
    if (n == 0)
        nlen += 1;
    while (FLAG_HAS(f, F_SIGN) && n != 0 && ++nlen)
        n /= f->base;
    while (!FLAG_HAS(f, F_SIGN) && n != 0 && ++nlen)
        n = (unsigned long long)n / f->base;

    if (nlen < (size_t)f->prec)
        nlen = f->prec;
    return (flen + nlen);
}

/* Load the number into string and store in the format to print later. */
void parse_nbr(long long n, t_format *f) {
    /* calculate length and add null terminator */
    int len = nbr_strlen(n, f);
    ft_memset(f->num, 0, len + 1);
    f->num[len] = '\0';

    /* check co-occurance of flag '0' and prefix(+/-/ ) */
    if (!FLAG_HAS(f, F_DOT)) {
        if (FLAG_HAS(f, F_ZERO) && FLAG_HAS(f, F_SIGN) &&
            (n < 0 || FLAG_HAS(f, F_PLUS) || FLAG_HAS(f, F_SPACE)))
            f->prec = f->width - 1;
        if (FLAG_HAS(f, F_ZERO) && !FLAG_HAS(f, F_SIGN))
            f->prec = f->width;
    }

    /* handle the prefixes (+/-/ /0x/0X) and the precision padding */
    if (FLAG_HAS(f, F_SIGN)) {
        if (n < 0)
            f->num[0] = '-';
        else if (FLAG_HAS(f, F_PLUS))
            f->num[0] = '+';
        else if (FLAG_HAS(f, F_SPACE))
            f->num[0] = ' ';
    }

    if ((((f->type == 'x' || f->type == 'X') && FLAG_HAS(f, F_HASH)) || f->type == 'p') && n != 0) {
        f->num[0] = '0';
        f->num[1] = f->type == 'X' ? 'X' : 'x';
    }

    const char *base = f->type == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";

    /* output number base on signs */
    if (FLAG_HAS(f, F_SIGN)) {
        while (n != 0 && --len >= 0) {
            if (n > 0)
                f->num[len] = base[n % f->base];
            else
                f->num[len] = base[-(n % f->base)];
            n /= f->base;
        }
    } else {
        while (n != 0 && --len >= 0) {
            f->num[len] = base[(unsigned long long)n % f->base];
            n = (unsigned long long)n / f->base;
        }
    }

    /* add leading 0s */
    while (--len >= 0 && !f->num[len])
        f->num[len] = '0';
}

/* Reset the format parameters to the initial states. */
static void reset_format(t_format *f) {
    f->type = 0;
    f->padding = ' ';
    f->flags = 0;
    f->width = 0;
    f->prec = 0;
    f->base = 10;
}

/* Handle the specifier 'c' and '%'. */
void print_char(char c, int *count, t_format *f) {
    size_t pad = (f->width > 1) ? (size_t)(f->width - 1) : 0;

    if (!FLAG_HAS(f, F_MINUS))
        *count += print_padding(f->padding, pad, f);

    emit(f, &c, 1);
    (*count)++;

    if (FLAG_HAS(f, F_MINUS))
        *count += print_padding(f->padding, pad, f);
}

/* Handle the specifier 's', and the number portion of 'diuxX'. */
int print_str(char *s, int *count, t_format *f) {
    if (!s) {
        if (!FLAG_HAS(f, F_DOT) || f->prec >= 6)
            return print_str(NULL_STR, count, f);
        return (0);
    }

    size_t len = ft_strlenf(s, f);
    size_t pad = (f->width > (int)len) ? (size_t)(f->width - len) : 0;

    if (!FLAG_HAS(f, F_MINUS))
        *count += print_padding(f->padding, pad, f);

    for (size_t i = 0; i < len; i++)
        emit(f, &s[i], 1);
    *count += len;

    if (FLAG_HAS(f, F_MINUS))
        *count += print_padding(f->padding, pad, f);
    return (1);
}

/* Handle the specifier 'diuxX'. */
void print_nbr(long long n, int *count, t_format *f) {
    parse_nbr(n, f);
    print_str(f->num, count, f);
}

/* Handle the specifier 'p'. */
void print_ptr(void *p, int *count, t_format *f) {
    if (!p && print_str(NULL_PTR, count, f))
        return;
    parse_nbr((long long)p, f);
    print_str(f->num, count, f);
}

void print_mem(void *p, int *count, t_format *f) {
    f->prec = 2;
    const unsigned char *b = p;
    for (int i = 0; i < 4; i++) {
        parse_nbr((long long)b[i], f);
        print_str(f->num, count, f);
    }
}

void print_bin(void *p, int *count, t_format *f) {
    f->prec = 8;
    const unsigned char *b = p;

    parse_nbr((long long)*b, f);
    print_str(f->num, count, f);
}

/* Print the next argument based on its specifier. */
void print_arg(va_list *args, int *count, t_format *f) {
    if (f->type == 'c')
        print_char(va_arg(*args, int), count, f);
    else if (f->type == 's')
        print_str(va_arg(*args, char *), count, f);
    else if (f->type == 'p')
        print_ptr(va_arg(*args, void *), count, f);
    else if (ft_strchr("di", f->type))
        print_nbr((long long)va_arg(*args, int), count, f);
    else if (ft_strchr("xXu", f->type))
        print_nbr((long long)va_arg(*args, unsigned int), count, f);
    else if (f->type == '%')
        print_char('%', count, f);
    else if (f->type == 'm')
        print_mem(va_arg(*args, void *), count, f);
    else if (f->type == 'b')
        print_bin(va_arg(*args, void *), count, f);
}
// m = actual memory layout with precision as how many bytes (default 4)
// b = in binary layout with precision as how many bytes (default 1)

/* Parse the template string char by char. */
static int parse(char *s, va_list *args, t_format *f) {
    int count = 0;

    while (*s) {
        if (*s == '%') {
            ++s;
            reset_format(f);
            parse_format(&s, args, f);
            print_arg(args, &count, f);
        } else {
            emit(f, s++, 1);
            ++count;
        }
    }
    return (count);
}

/* Mimic the system printf function, works with cspdiuxX%. */
int ft_printf(const char *s, ...) {
    int count;
    va_list args;
    t_format format;

    reset_format(&format);
    format.mode = MODE_FD;
    format.fd = STDOUT_FILENO;

    va_start(args, s);
    count = parse((char *)s, &args, &format);
    va_end(args);
    return (count);
}

int ft_dprintf(int fd, const char *s, ...) {
    int count;
    va_list args;
    t_format format;

    reset_format(&format);
    format.mode = MODE_FD;
    format.fd = fd;

    va_start(args, s);
    count = parse((char *)s, &args, &format);
    va_end(args);
    return (count);
}

int ft_snprintf(char *buf, size_t size, const char *s, ...) {
    int count;
    va_list args;
    t_format format;

    reset_format(&format);
    format.mode = MODE_BUF;
    format.buf = buf;
    format.buf_size = size;
    format.buf_pos = 0;

    va_start(args, s);
    count = parse((char *)s, &args, &format);
    va_end(args);

    /* Null-terminate if possible */
    if (size > 0) {
        if (format.buf_pos >= size)
            buf[size - 1] = '\0';
        else
            buf[format.buf_pos] = '\0';
    }

    return count;
}

int ft_vsnprintf(char *buf, size_t size, const char *s, va_list args) {
    t_format format;
    int count;

    reset_format(&format);
    format.mode = MODE_BUF;
    format.buf = buf;
    format.buf_size = size;
    format.buf_pos = 0;

    count = parse((char *)s, &args, &format);

    if (size > 0) {
        if (format.buf_pos >= size)
            buf[size - 1] = '\0';
        else
            buf[format.buf_pos] = '\0';
    }

    return count;
}

int ft_asprintf(char **out, const char *s, ...) {
    va_list args;
    int len;

    /* First pass: count only */
    va_start(args, s);
    len = ft_vsnprintf(NULL, 0, s, args);
    va_end(args);

    *out = malloc((size_t)len + 1);
    if (!*out)
        return (-1);

    /* Second pass: real write */
    va_start(args, s);
    ft_vsnprintf(*out, (size_t)len + 1, s, args);
    va_end(args);

    return len;
}

int ft_vasprintf(char **out, const char *s, va_list args) {
    va_list copy;
    int len;

    va_copy(copy, args);
    len = ft_vsnprintf(NULL, 0, s, copy);
    va_end(copy);

    *out = malloc((size_t)len + 1);
    if (!*out)
        return (-1);

    ft_vsnprintf(*out, (size_t)len + 1, s, args);
    return len;
}
