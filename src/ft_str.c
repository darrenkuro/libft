/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:19:11 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 09:53:32 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc, size_t, NULL

size_t ft_strlen(const char *s) {
    size_t len;

    len = 0;
    while (*s++)
        ++len;
    return (len);
}

char *ft_strchr(const char *s, int c) {
    int i;

    i = -1;
    while (s[++i])
        if (s[i] == (char)c)
            return ((char *)&s[i]);
    if (c == '\0')
        return ((char *)&s[i]);
    return (NULL);
}

char *ft_strrchr(const char *s, int c) {
    int i;

    i = ft_strlen(s) + 1;
    while (--i >= 0)
        if (s[i] == (char)c)
            return ((char *)&s[i]);
    return (NULL);
}

char *ft_substr(char const *s, unsigned int start, size_t len) {
    char *str;
    size_t slen;
    size_t i;

    if (!s)
        return (NULL);
    slen = ft_strlen(s);
    if (start >= slen)
        len = 0;
    else if (len > slen - start)
        len = slen - start;
    str = malloc((len + 1) * sizeof(char));
    if (!str)
        return (NULL);
    i = -1;
    while (++i < len)
        str[i] = s[start + i];
    str[i] = '\0';
    return (str);
}

int ft_strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0 && *s1 && *s2 && n--)
        if (*s1++ != *s2++)
            return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
    if (n == 0)
        return (0);
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t ft_strlcat(char *dst, const char *src, size_t dstsize) {
    size_t dst_len;
    size_t src_len;

    src_len = ft_strlen(src);
    if (!dst && dstsize == 0)
        return (src_len);
    dst_len = ft_strlen(dst);
    if (dstsize < dst_len + 1)
        return (src_len + dstsize);
    dstsize -= dst_len;
    dst += dst_len;
    while (*src && --dstsize > 0)
        *dst++ = *src++;
    *dst = '\0';
    return (src_len + dst_len);
}

char *ft_strdup(const char *s1) {
    char *dup;
    size_t len;

    len = ft_strlen(s1);
    dup = malloc((len + 1) * sizeof(char));
    if (!dup)
        return (NULL);
    while (*s1)
        *dup++ = *s1++;
    *dup = '\0';
    return (dup - len);
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize) {
    size_t i;

    i = -1;
    if (!dstsize)
        return (ft_strlen(src));
    while (++i < dstsize - 1 && src[i])
        dst[i] = src[i];
    dst[i] = '\0';
    return (ft_strlen(src));
}

char *ft_strtrim(char const *s1, char const *set) {
    size_t start;
    size_t end;

    if (!s1)
        return (NULL);
    if (!set)
        return (ft_strdup(s1));
    start = 0;
    end = ft_strlen(s1) - 1;
    while (s1[start] && ft_strchr(set, s1[start]))
        ++start;
    while (s1[end] && ft_strchr(set, s1[end]) && end > 0)
        --end;
    if (start > end + 1)
        return (ft_strdup(""));
    return (ft_substr(s1, start, end - start + 1));
}

char *ft_strjoin(char const *s1, char const *s2) {
    char *str;
    size_t len;

    if (!s1 || !s2)
        return (NULL);
    len = ft_strlen(s1) + ft_strlen(s2) + 1;
    str = malloc(len * sizeof(char));
    if (!str)
        return (NULL);
    ft_strlcpy(str, s1, len);
    ft_strlcat(str, s2, len);
    return (str);
}

char *ft_strnstr(const char *haystack, const char *needle, size_t len) {
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    if (!*needle)
        return ((char *)haystack);
    while (i < len && haystack[i]) {
        while ((i + j) < len && haystack[i + j] == needle[j] && haystack[i + j])
            ++j;
        if (!needle[j])
            return ((char *)haystack + i);
        j = 0;
        ++i;
    }
    return (NULL);
}

void ft_striteri(char *s, void (*f)(unsigned int, char *)) {
    int i;

    i = -1;
    if (!s || !f)
        return;
    while (s[++i])
        f((unsigned int)i, &s[i]);
}

char *ft_strmapi(char const *s, char (*f)(unsigned int, char)) {
    char *ret;
    int i;

    i = -1;
    if (!s)
        return (NULL);
    ret = malloc((ft_strlen(s) + 1) * sizeof(char));
    if (!ret)
        return (NULL);
    while (s[++i])
        ret[i] = f((unsigned int)i, s[i]);
    ret[i] = '\0';
    return (ret);
}

/* ================ split ============== */

static int ft_split_count(char const *s, char c) {
    int count;
    int len;
    int i;

    count = 0;
    len = 0;
    i = -1;
    if (!s || !*s)
        return (count);
    while (s[++i]) {
        if (s[i] != c)
            ++len;
        else if (len && s[i] == c && ++count)
            len = 0;
    }
    if (s[i - 1] == c)
        return (count);
    else
        return (count + 1);
}

static char **alloc_result(char const *s, char c) {
    char **ret;

    ret = malloc((ft_split_count(s, c) + 1) * sizeof(char *));
    if (!ret)
        return (NULL);
    ret[0] = NULL;
    return (ret);
}

static int fill_result(char **ret, char const *s, char c, int k) {
    int i;
    int len;

    i = -1;
    len = 0;
    while (s[++i]) {
        if ((s[i] != c))
            len++;
        else if (len) {
            ret[k++] = ft_substr(s + i - len, 0, len);
            if (!ret[k - 1])
                return (0);
            len = 0;
        }
    }
    if (len) {
        ret[k++] = ft_substr(s + i - len, 0, len);
        if (!ret[k - 1])
            return (0);
    }
    ret[k] = NULL;
    return (1);
}

static void free_result(char **ret) {
    int i;

    i = 0;
    while (ret[i])
        free(ret[i++]);
    free(ret);
}

char **ft_split(const char *s, char c) {
    char **ret;
    int k;

    k = 0;
    if (!s)
        return (NULL);
    ret = alloc_result(s, c);
    if (!ret)
        return (NULL);
    if (!fill_result(ret, s, c, k)) {
        free_result(ret);
        return (NULL);
    }
    return (ret);
}
