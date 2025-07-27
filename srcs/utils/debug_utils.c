/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:04:40 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 18:04:40 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static const char	*get_token_type_name(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == OUTFILE)
		return ("OUTFILE");
	else if (type == INFILE)
		return ("INFILE");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == AND_IF)
		return ("AND_IF");
	else if (type == OR)
		return ("OR");
	else if (type == PARENTHESIS)
		return ("PARENTHESIS");
	return ("UNKNOWN");
}

static const char	*get_token_state_name(t_token_state state)
{
	if (state == GENERAL)
		return ("GENERAL");
	else if (state == IN_DQUOTES)
		return ("IN_DQUOTES");
	else if (state == IN_SQUOTES)
		return ("IN_SQUOTES");
	else if (state == EXPAND)
		return ("EXPAND");
	return ("UNKNOWN");
}

void	print_tokens(t_list *token_lst)
{
	t_token	*token;
	int		i;

	if (!token_lst)
	{
		printf("  (no tokens)\n");
		return ;
	}
	
	printf("+-----------------+------------+--------------+--------+\n");
	printf("|     Value       |    Type    |    State     |  Pos   |\n");
	printf("+-----------------+------------+--------------+--------+\n");
	
	i = 0;
	while (token_lst)
	{
		token = (t_token *)token_lst->content;
		printf("| %-15s | %-10s | %-12s | %-6d |\n",
			token->value ? token->value : "(null)",
			get_token_type_name(token->type),
			get_token_state_name(token->state),
			token->pos);
		token_lst = token_lst->next;
		i++;
	}
	
	printf("+-----------------+------------+--------------+--------+\n");
	printf("Total tokens: %d\n", i);
}