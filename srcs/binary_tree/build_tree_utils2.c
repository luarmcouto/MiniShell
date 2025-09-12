/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:38:47 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:18:56 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*skip_if(t_list *tmp)
{
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tmp = tmp->next;
		if (!check_tree_token(tmp))
			break ;
	}
	return (tmp);
}

bool	check_tree_token(t_list *node)
{
	if (!node)
		return (false);
	
	// Verifica se o token não é um operador lógico
	if (((t_token *)node->content)->type == AND_IF ||
	    ((t_token *)node->content)->type == OR)
		return (false);
		
	return (true);
}

t_list	*skip_else(t_list *tmp)
{
	tmp = tmp->next;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tmp = tmp->next;
		if (!check_tree_token(tmp))
			break ;
	}
	return (tmp);
}

t_list	*check_word(t_list **current, char **argv, int *i)
{
	if (*current && ((t_token *)(*current)->content)->state == EXPAND
		&& ft_strlen(((t_token *)(*current)->content)->value) == 0)
	{
		*current = (*current)->next;
		return (*current);
	}
	argv[*i] = ((t_token *)(*current)->content)->value;
	*current = (*current)->next;
	(*i)++;
	return (*current);
}

t_list	*check_w_args(t_list *tkn_lst, int *args)
{
	if (tkn_lst && ((t_token *)tkn_lst->content)->type == WORD)
	{
		if (((t_token *)tkn_lst->content)->state == EXPAND
			&& ft_strlen(((t_token *)tkn_lst->content)->value) == 0)
		{
			return (tkn_lst->next);
		}
		(*args)++;
	}
	return (tkn_lst->next);
}