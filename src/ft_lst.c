/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:14:22 by dlu               #+#    #+#             */
/*   Updated: 2025/12/30 08:35:05 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h> // malloc, NULL

t_list *ft_lstnew(void *content) {
    t_list *node;

    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

t_list *ft_lstlast(t_list *lst) {
    while (lst && lst->next)
        lst = lst->next;
    return (lst);
}

int ft_lstsize(t_list *lst) {
    int size;

    if (!lst)
        return (0);
    size = 1;
    while (lst && lst->next && ++size)
        lst = lst->next;
    return (size);
}

void ft_lstadd_front(t_list **lst, t_list *node) {
    if (!lst)
        return;
    node->next = *lst;
    *lst = node;
}

void ft_lstadd_back(t_list **lst, t_list *node) {
    if (!lst)
        return;
    if (!*lst)
        *lst = node;
    else
        ft_lstlast(*lst)->next = node;
}

void ft_lstiter(t_list *lst, void (*f)(void *)) {
    int size;

    if (!lst || !f)
        return;
    size = ft_lstsize(lst);
    while (--size >= 0) {
        f(lst->content);
        lst = lst->next;
    }
}

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)) {
    t_list *ret;
    t_list *tmp;

    if (!lst || !f)
        return (NULL);
    ret = NULL;
    while (lst) {
        tmp = ft_lstnew((*f)(lst->content));
        if (!tmp) {
            ft_lstclear(&ret, del);
            return (NULL);
        }
        ft_lstadd_back(&ret, tmp);
        lst = lst->next;
    }
    return (ret);
}

void ft_lstdelone(t_list *lst, void (*del)(void *)) {
    if (!lst || !del)
        return;
    del(lst->content);
    free(lst);
}

void ft_lstclear(t_list **lst, void (*del)(void *)) {
    t_list *temp;

    if (!lst || !del)
        return;
    while (*lst) {
        temp = (*lst)->next;
        del((*lst)->content);
        free(*lst);
        *lst = temp;
    }
    lst = NULL;
}
