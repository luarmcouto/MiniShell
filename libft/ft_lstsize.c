/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:46:19 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 16:51:03 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		++counter;
		lst = lst->next;
	}
	return (counter);
}
/*
int	main(void)
{
    // Criando uma lista encadeada com três elementos
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));

    // Configurando os ponteiros next dos nós
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    // Contando o número de elementos na lista
    int size = ft_lstsize(node1);

    // Imprimindo o tamanho da lista
    printf("Tamanho da lista: %d\n", size);

    // Liberando a memória alocada para os nós
    free(node1);
    free(node2);
    free(node3);

    return (0);
}*/