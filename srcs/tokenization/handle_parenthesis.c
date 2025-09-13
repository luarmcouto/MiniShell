/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:08:39 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/09 09:08:39 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Forward declarations para evitar conflitos de tipo
static int		handle_closing(t_shell *shell, char *input, int i, bool valid);
static int		check_balance(char *input, int i);
static bool		validate_subs(char *subs);
static int		handle_opening(t_shell *shell, char *input, int i, bool valid);
static int		jump_spaces(char *input, int i);

int	handle_parenthesis(t_shell *shell, char *input, int i)
{
	static bool	valid = false;
	int			start;
	char		*subs;

	if (input[i] == ')')
	{
		i = handle_closing(shell, input, i, valid);
		if (i != -1)
			return (i);
	}
	start = i;
	i = check_balance(input, i);
	subs = ft_substr(&input[start + 1], 0, i - start - 1);
	valid = validate_subs(subs);
	free(subs);
	i = handle_opening(shell, input, start, valid);
	if (i != -1)
		return (i);
	if (input[start] && input[start] == '(')
		start++;
	while (ft_isspace(input[start]))
		start++;
	return (start);
}

static int	check_balance(char *input, int i)
{
	int	balance;

	balance = 0;
	
	while (input[i])
	{
		if (input[i] == '(')
			balance++;
		else if (input[i] == ')')
		{
			balance--;
			if (balance == 0)
				break;
		}
		i++;
	}
	
	return (i);
}

static bool	validate_subs(char *subs)
{
	char	*tkns;
	int		j;
	int		i;

	tkns = "|&";
	j = 0;
	i = 0;
	if (!subs || i < 0)
		return (false);
	while (subs[i])
	{
		j = 0;
		while (tkns[j])
		{
			if (subs[i] && subs[i] == tkns[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static int	jump_spaces(char *input, int i)
{
	i++;
	while (ft_isspace(input[i]))
		i++;
	return (i);
}

static int	handle_closing(t_shell *shell, char *input, int i, bool valid)
{
	t_token	*new_token;
	char	*str;

	if (input[i] == ')' && valid)
	{
		str = ft_strdup(")");
		i++;
		if (!str)
			exit_failure(shell, "handle_parenthesis");
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
		{
			free(str);
			exit_failure(shell, "handle_parenthesis");
		}
		new_token->value = str;
		new_token->type = PARENTHESIS;
		new_token->state = GENERAL;
		ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
		while (ft_isspace(input[i]))
			i++;
		return (i);
	}
	else
	{
		i = jump_spaces(input, i);
		return (i);
	}
}

static int	handle_opening(t_shell *shell, char *input, int i, bool valid)
{
	t_token		*new_token;
	char		*str;

	if (valid)
	{
		str = NULL;
		if (input[i] == '(')
			str = ft_strdup("(");
		else if (input[i] == ')')
			str = ft_strdup(")");
		
		i++;
		if (!str)
			exit_failure(shell, "handle_parenthesis");
		
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
		{
			free(str);
			exit_failure(shell, "handle_parenthesis");
		}
		new_token->value = str;
		new_token->type = PARENTHESIS;
		new_token->state = GENERAL;
		ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
		
		while (ft_isspace(input[i]))
			i++;
		return (i);
	}
	return (-1);
}
