/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:36:25 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 17:11:55 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (NULL == lst)
		return ;
	if (NULL == *lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*
int	main()
{
	t_list	*head, *node_1, *node_2;

	head = malloc(sizeof(t_list));
	node_1 = malloc(sizeof(t_list));
	node_2 = malloc(sizeof(t_list));

	head->content = (void *)"Vamos";
	node_1->content = (void *)"Inter";
	node_2->content = (void *)"!";
	
	ft_lstadd_back(&head, node_1);
	ft_lstadd_back(&head, node_2);

	t_list	*current;
	
	current = head;
	while (current)
	{
		printf("%s\n", (char *)(current->content));
		current = current->next;
	}
}*/