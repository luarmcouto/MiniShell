/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:03 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 15:52:40 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (NULL == node)
	{
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
int	main(void)
{
    // Criando um novo nó da lista
    t_list *node = ft_lstnew("Vamo, inter!");

    // Verificando se o nó foi criado com sucesso
    if (node == NULL)
    {
        printf("Erro: falha ao criar um novo nó da lista.\n");
        return (1);
    }

    // Exibindo o conteúdo do nó
    printf("Conteúdo do nó: %s\n", (char *)node->content);

    // Liberando a memória alocada para o nó
    free(node);

    return (0);
}*/