/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:55:23 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:55:23 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	in_quotes(char *input, int i)
{
	if (input[i] == '"')
		return (true);
	return (false);
}

int	set_append(t_shell *sh, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 2);
	if (!new_token->value)
		exit_failure(sh, "set_append");
	new_token->type = APPEND;
	return (i + 2);
}

int	set_simple(t_shell *sh, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 1);
	if (!new_token->value)
		exit_failure(sh, "set_simple");
	if (input[i] == '<')
		new_token->type = INFILE;
	else
		new_token->type = OUTFILE;
	return (i + 1);
}

bool	is_expandable(char *token)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (ft_isspace(token[i]))
		i++;
	if (token[i] == '\0')
		return (false);
	while (token[i])
	{
		if (ft_isquote(token[i]))
		{
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		if (token[i] == '$' && (token[i + 1] == '?'
				|| ft_isalnum(token[i + 1])))
			return (true);
		if (!in_quotes && (ft_isspace(token[i]) || ft_ismeta(token, i)))
			return (false);
		i++;
	}
	return (false);
}
