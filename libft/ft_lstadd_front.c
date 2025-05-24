/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:05:42 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 16:46:36 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int main() {
    t_list *head = ft_lstnew("Internacional");
    if (head == NULL) {
        printf("Falha ao criar o node\n");
        return 1;
    }

    t_list *new_node1 = ft_lstnew("Gigante");
    if (new_node1 == NULL) {
        printf("Falha ao criar o node\n");
        return 1;
    }

    ft_lstadd_front(&head, new_node1);

    t_list *current = head;
    while (current != NULL) {
        printf("Conteudo do node: %s\n", (char *)current->content);
        current = current->next;
    }

    while (head != NULL) {
        t_list *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}*/