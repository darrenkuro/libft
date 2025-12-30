/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:58:18 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 10:11:51 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h> // free, NULL
#include <unistd.h> // write

/* Helper function to replace write so it can write to memory as well. */
static void emit(t_format *f, const char *s, size_t n) {
    if (f->mode == MODE_FD) {
        write(f->fd, s, n);
    } else {
        size_t i = 0;
        while (i < n && f->buf_pos + 1 < f->buf_size) {
            f->buf[f->buf_pos++] = s[i++];
        }
    }
}

/* Return the length to be printed for a given string. */
int ft_strlenf(char *s, t_format *f) {
    int i;

    if (!s || (f->type == 's' && f->dot && f->precision == 0))
        return (0);
    i = -1;
    while (s[++i])
        if (f->type == 's' && f->dot && i >= f->precision)
            return (i);
    return (i);
}

/* Print the padding and return the length of the padding printed. */
int print_padding(char c, int len, t_format *f) {
    int i;

    if (len <= 0)
        return (0);
    i = -1;
    while (++i < len)
        emit(f, &c, 1);
    return (len);
}

/* Parse the flags in order. */
static void parse_flags(char **s, t_format *f) {
    while (**s == '#' && (*s)++)
        f->hash = 1;
    while (**s == '-' && (*s)++)
        f->minus = 1;
    while (**s == '+' && (*s)++)
        f->plus = 1;
    while (**s == ' ' && (*s)++)
        f->space = 1;
    while (**s == '0' && (*s)++)
        f->zero = 1;
    if (f->plus)
        f->space = 0;
    if (f->minus)
        f->zero = 0;
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
        f->dot = 1;
        (*s)++;
    }
    if (**s == '*') {
        f->precision = va_arg(*args, int);
        if (f->precision < 0)
            f->precision = 0;
        (*s)++;
        return;
    }
    while (**s >= '0' && **s <= '9') {
        f->precision = (f->precision * 10) + **s - '0';
        (*s)++;
    }
}

/* Parse the format and set its parameters. */
void parse_format(char **s, va_list *args, t_format *f) {
    parse_flags(s, f);
    parse_width(s, args, f);
    parse_precision(s, args, f);
    f->type = **s;
    if (**s == 'p' || **s == 'x' || **s == 'X')
        f->base = 16;
    if (**s == 'd' || **s == 'i')
        f->signed_nbr = 1;
    if (f->zero)
        f->padding = '0';
    if (f->dot && f->zero)
        f->padding = ' ';
    (*s)++;
}

/* Return the length of the nbr, excluding '-'. */
static int nbr_len(long long n, t_format *f) {
    int len;

    len = 0;
    if (n == 0)
        return (++len);
    while (f->signed_nbr && n != 0 && ++len)
        n /= f->base;
    while (!f->signed_nbr && n != 0 && ++len)
        n = (unsigned long long)n / f->base;
    return (len);
}

/* Return the length of the nbr string, excluding '\0'. */
static int nbr_strlen(long long n, t_format *f) {
    int len;

    len = nbr_len(n, f);
    if (f->dot && !f->precision && n == 0)
        return (0);
    if (len < f->precision)
        len = f->precision;
    if (f->signed_nbr && (n < 0 || f->plus || f->space))
        ++len;
    if ((((f->type == 'x' || f->type == 'X') && f->hash) || f->type == 'p') && n != 0)
        len += 2;
    return (len);
}

/* Handle the prefixes (+/-/ /0x/0X) and the precision padding. */
static void nbr_prefix(long long n, t_format *format, int len) {
    if (format->signed_nbr) {
        if (n < 0)
            format->num[0] = '-';
        else if (format->plus)
            format->num[0] = '+';
        else if (format->space)
            format->num[0] = ' ';
    }
    if ((((format->type == 'x' || format->type == 'X') && format->hash) || format->type == 'p') &&
        n != 0) {
        format->num[0] = '0';
        if (format->type == 'X')
            format->num[1] = 'X';
        else
            format->num[1] = 'x';
    }
    while (--len >= 0 && !format->num[len])
        format->num[len] = '0';
}

/* Handle the co-occurance of flag '0' and prefix(+/-/ ). */
static void nbr_flag_zero(t_format *format) {
    if (!format->dot) {
        if (format->zero && format->signed_nbr &&
            (format->nbr < 0 || format->plus || format->space))
            format->precision = format->width - 1;
        if (format->zero && !format->signed_nbr)
            format->precision = format->width;
    }
}

/* Load the number into string and store in the format to print later. */
void parse_nbr(long long n, const char *base, t_format *format) {
    int len;

    nbr_flag_zero(format);
    len = nbr_strlen(n, format) + 1;
    format->num = ft_calloc(len, sizeof(char));
    if (!format->num)
        return;
    format->num[--len] = '\0';
    while (format->signed_nbr && n != 0 && --len >= 0) {
        if (n > 0)
            format->num[len] = base[n % format->base];
        else
            format->num[len] = base[-(n % format->base)];
        n /= format->base;
    }
    while (!format->signed_nbr && n != 0 && --len >= 0) {
        format->num[len] = base[(unsigned long long)n % format->base];
        n = (unsigned long long)n / format->base;
    }
    nbr_prefix(format->nbr, format, len);
}

/* Reset the format parameters to the initial states. */
static void reset_format(t_format *format) {
    format->nbr = 0;
    format->type = 0;
    format->padding = ' ';
    format->num = NULL;
    format->hash = 0;
    format->minus = 0;
    format->plus = 0;
    format->space = 0;
    format->dot = 0;
    format->zero = 0;
    format->width = 0;
    format->precision = 0;
    format->base = 10;
    format->signed_nbr = 0;
}

/* Handle the specifier 'c' and '%'. */
void print_char(char c, int *count, t_format *f) {
    if (!f->minus)
        *count += print_padding(f->padding, f->width - 1, f);
    emit(f, &c, 1);
    (*count)++;
    if (f->minus)
        *count += print_padding(f->padding, f->width - 1, f);
}

/* Handle the specifier 's', and the number portion of 'diuxX'. */
int print_str(char *s, int *count, t_format *f) {
    int len;
    int i;

    if (!s && !f->dot && print_str(NULL_STR, count, f))
        return (0);
    else if (!s && f->precision >= 6 && print_str(NULL_STR, count, f))
        return (0);
    len = ft_strlenf(s, f);
    if (!f->minus)
        *count += print_padding(f->padding, f->width - len, f);
    i = -1;
    while (++i < len)
        emit(f, &s[i], 1);
    *count += len;
    if (f->minus)
        *count += print_padding(f->padding, f->width - len, f);
    return (1);
}

/* Handle the specifier 'diuxX'. */
void print_nbr(long long n, const char *base, int *count, t_format *f) {
    f->nbr = n;
    parse_nbr(f->nbr, base, f);
    print_str(f->num, count, f);
    free(f->num);
}

/* Handle the specifier 'p'. */
void print_ptr(void *p, int *count, t_format *f) {
    if (!p && print_str(NULL_PTR, count, f))
        return;
    f->nbr = (long long)p;
    parse_nbr(f->nbr, HEXL, f);
    print_str(f->num, count, f);
    free(f->num);
}

/* Print the next argument based on its specifier. */
void print_arg(va_list *args, int *count, t_format *format) {
    if (format->type == 'c')
        print_char(va_arg(*args, int), count, format);
    else if (format->type == 's')
        print_str(va_arg(*args, char *), count, format);
    else if (format->type == 'p')
        print_ptr(va_arg(*args, void *), count, format);
    else if (format->type == 'd' || format->type == 'i')
        print_nbr((long long)va_arg(*args, int), DEC, count, format);
    else if (format->type == 'x')
        print_nbr((long long)va_arg(*args, unsigned int), HEXL, count, format);
    else if (format->type == 'X')
        print_nbr((long long)va_arg(*args, unsigned int), HEXU, count, format);
    else if (format->type == 'u')
        print_nbr((long long)va_arg(*args, unsigned int), DEC, count, format);
    else if (format->type == '%')
        print_char('%', count, format);
}

/* Parse the template string char by char. */
static int parse(char *s, va_list *args, t_format *format) {
    int count;

    count = 0;
    while (*s) {
        if (*s == '%') {
            ++s;
            reset_format(format);
            parse_format(&s, args, format);
            print_arg(args, &count, format);
        } else {
            emit(format, s++, 1);
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
