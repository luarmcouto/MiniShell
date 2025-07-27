/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:30:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/21 21:42:01 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

int	ft_isredir(char *c)
{
	if (c[0] == '>')
	{
		if (c[1] == '>')
			return (2);
		return (1);
	}
	if (c[0] == '<')
	{
		if (c[1] == '<')
			return (2);
		return (1);
	}
	return (0);
}

void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	else if (c == '\"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
}

int	jump_quotes(char *str, int i)
{
	if (str[i] && ft_isquote(str[i]))
	{
		i++;
		while (str[i] && !ft_isquote(str[i]))
			i++;
	}
	return (i);
}

bool	handle_redir_error(char *str, int *i, int redir_len)
{
	char	*error_msg;

	if (str[*i + 1] == '|')
	{
		syntax_error_msg("near unexpected token `|'");
		return (false);
	}
	*i += redir_len;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (ft_isredir(&str[*i]) || ft_ismeta(str, *i))
	{
		if (str[*i] == '>' && str[*i + 1] == '>')
			error_msg = "near unexpected token `>>'";
		else if (str[*i] == '<')
			error_msg = "near unexpected token `<'";
		else
			error_msg = "near unexpected token `>'";
		syntax_error_msg(error_msg);
		return (false);
	}
	return (true);
}