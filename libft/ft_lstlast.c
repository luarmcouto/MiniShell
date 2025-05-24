/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:58:43 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 17:00:37 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (NULL == lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));

    // Configurando os ponteiros next dos nós
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    // Encontrando o último elemento da lista
    t_list *last_node = ft_lstlast(node1);

    // Verificando se o último elemento foi encontrado
    if (last_node != NULL)
        printf("O último elemento da lista tem conteúdo: %p\n",
		last_node->content);
    else
        printf("A lista está vazia!\n");

    // Liberando a memória alocada para os nós
    free(node1);
    free(node2);
    free(node3);

    return (0);
}*/