/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_temp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:00:43 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 18:00:43 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Placeholder temporário para handle_or
int	handle_or(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	(void)shell;
	(void)input;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_or");
	
	new_token->value = ft_strdup("||");
	if (!new_token->value)
		exit_failure(shell, "handle_or");
	
	new_token->type = OR;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i += 2;
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

// Placeholder temporário para handle_parenthesis
int	handle_parenthesis(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_parenthesis");
	
	if (input[i] == '(')
		new_token->value = ft_strdup("(");
	else
		new_token->value = ft_strdup(")");
	
	if (!new_token->value)
		exit_failure(shell, "handle_parenthesis");
	
	new_token->type = PARENTHESIS;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i++;
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

// Placeholder temporário para handle_andif
int	handle_andif(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_andif");
	
	new_token->value = ft_strdup("&&");
	if (!new_token->value)
		exit_failure(shell, "handle_andif");
	
	new_token->type = AND_IF;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i += 2;
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}