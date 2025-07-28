/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:57:11 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:57:11 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_token_pos(t_list *lst)
{
	t_token	*token;
	int		i;

	i = 0;
	while (lst)
	{
		token = (t_token *) lst->content;
		token->pos = i;
		lst = lst->next;
		i++;
	}
}