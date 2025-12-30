/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 09:25:24 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 09:52:23 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"     // ft_substr
#include <fcntl.h>     // io flags
#include <limits.h>    // size_t
#include <stdbool.h>   // bool
#include <stddef.h>    // NULL
#include <stdlib.h>    // free
#include <sys/types.h> // ssize_t
#include <unistd.h>    // read

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#define BASE 10
#define INT_MIN_STR "-2147483648"

void ft_putchar_fd(char c, int fd) {
    if (fd < 0)
        return;
    write(fd, &c, 1);
}

void ft_putendl_fd(char *s, int fd) {
    if (!s || fd < 0)
        return;
    ft_putstr_fd(s, fd);
    ft_putstr_fd("\n", fd);
}

void ft_putnbr_fd(int n, int fd) {
    if (fd < 0)
        return;
    if (n == INT_MIN)
        ft_putstr_fd(INT_MIN_STR, fd);
    else if (n < 0) {
        ft_putchar_fd('-', fd);
        ft_putnbr_fd(-n, fd);
    } else if (n < BASE)
        ft_putchar_fd(n + '0', fd);
    else {
        ft_putnbr_fd(n / BASE, fd);
        ft_putnbr_fd(n % BASE, fd);
    }
}

void ft_putstr_fd(char *s, int fd) {
    if (!s || fd < 0)
        return;
    write(fd, s, ft_strlen(s));
}

static bool file_len(const char *filename) {
    int fd;
    int len;
    int size_read;
    char buffer[BUFFER_SIZE];

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (false);
    len = 0;
    while (true) {
        size_read = read(fd, buffer, BUFFER_SIZE);
        if (!size_read)
            break;
        len += size_read;
    }
    close(fd);
    return (len);
}

char *ft_read_file(const char *filename) {
    int fd;
    int idx;
    char *ret;
    char buffer[1];

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    ret = malloc((file_len(filename) + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    idx = 0;
    while (read(fd, buffer, 1))
        ret[idx++] = *buffer;
    ret[idx] = '\0';
    close(fd);
    return (ret);
}

/* ======================= get next line ========================= */

/* Return the index of '\n', or the index of the '\0' if at the end. */
static int nl_index(char *prev, int end) {
    int i;

    if (!prev)
        return (-1);
    i = -1;
    while (prev[++i])
        if (prev[i] == '\n')
            return (i);
    if (end)
        return (i);
    else
        return (-1);
}

/* Append buffer to prev, return 1 for success, 0 for failure. */
static int append_buffer(char **prev, char *buffer, ssize_t n) {
    char *tmp;
    int len;
    int i;

    if (n < 0)
        return (0);
    len = ft_strlen(*prev);
    tmp = malloc((len + n + 1) * sizeof(char));
    if (!tmp)
        return (0);
    i = -1;
    while (++i < len)
        *tmp++ = (*prev)[i];
    while (++i < len + n + 1)
        *tmp++ = *buffer++;
    *tmp = '\0';
    free(*prev);
    *prev = tmp - len - n;
    return (1);
}

/* Free the buffer and update with prev with replacement. */
static char *update_prev(char **prev, char *replace, char **buffer) {
    if (*buffer != NULL) {
        free(*buffer);
        *buffer = NULL;
    }
    if (*prev != NULL) {
        free(*prev);
        *prev = replace;
    }
    return (*prev);
}

/* Return the next line, and update the prev to next byte (both copy and free).
 * Prev str has to include a '\n' at index, unless it's at the end.
 * Return NULL if any malloc fails, with all allocated resources freed. */
static char *process_prev(char **prev, int index, int end, char **buffer) {
    char *line;
    char *tmp;

    if (end && !ft_strlen(*prev))
        return (update_prev(prev, NULL, buffer));
    if ((*prev)[index] == '\n') {
        line = ft_substr(*prev, 0, index + 1);
        tmp = ft_substr(*prev, index + 1, ft_strlen(*prev) - index - 1);
        update_prev(prev, tmp, buffer);
        if (!tmp)
            return (free(line), free(*buffer), NULL);
    } else {
        line = ft_substr(*prev, 0, index);
        update_prev(prev, NULL, buffer);
    }
    if (!line)
        return (update_prev(prev, NULL, buffer));
    return (line);
}

/* Process next line overhead, protect against faulty BUFFER_SIZE (0). */
static char *process_next_line(int fd, char **prev) {
    ssize_t read_bytes;
    char *buffer;

    buffer = malloc(BUFFER_SIZE * sizeof(char));
    if (!buffer)
        return (update_prev(prev, NULL, &buffer));
    while (nl_index(*prev, 0) < 0) {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (!append_buffer(prev, buffer, read_bytes))
            return (update_prev(prev, NULL, &buffer));
        if (read_bytes < BUFFER_SIZE)
            return (process_prev(prev, nl_index(*prev, 1), 1, &buffer));
    }
    return (process_prev(prev, nl_index(*prev, 0), 0, &buffer));
}

/* Get the next line of a file descriptor. */
char *get_next_line(int fd) {
    static char *prev;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!prev) {
        prev = malloc(sizeof(char));
        if (!prev)
            return (NULL);
        prev[0] = '\0';
    }
    return (process_next_line(fd, &prev));
}
