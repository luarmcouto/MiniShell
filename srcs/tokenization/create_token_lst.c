/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:52:23 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:52:23 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:41:24 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/29 14:41:24 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO : Diminuir funções

#include <minishell.h>

#include <minishell.h>

void	tokenize_input(t_shell *shell, char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
			i = handle_or(shell, input, i);
		else if (input[i] == '|')
			i = handle_pipe(shell, input, i);
		else if (input[i] == '(' || input[i] == ')')
			i = handle_parenthesis(shell, input, i);
		else if (input[i] == '&' && input[i + 1] == '&')
			i = handle_andif(shell, input, i);
		else if (input[i] == '>' || input[i] == '<')
			i = handle_redir(shell, input, i);
		else if (ft_isspace(input[i]))
		{
			while (ft_isspace(input[i]))
				i++;
		}
		else
			i = handle_word_token(shell, input, i);
		set_token_pos(shell->token_lst);
	}
}

int	handle_word_token(t_shell *shell, char *input, int i)
{
	t_token	*new_token;
	char	*str;
	int		start;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_word_token");
	
	start = i;
	
	// Pular até encontrar espaço ou metacharacter
	while (input[i] && !ft_isspace(input[i]) && !ft_ismeta(input, i))
	{
		if (ft_isquote(input[i]))
		{
			char quote = input[i];
			i++; // pula a quote inicial
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++; // pula a quote final
		}
		else
			i++;
	}
	
	// Extrair a substring
	str = ft_substr(input, start, i - start);
	if (!str)
		exit_failure(shell, "handle_word_token");
	
	new_token->value = str;
	new_token->type = WORD;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	return (i);
}

int	handle_redir(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_redir");
	
	if (input[i] == '>' && input[i + 1] == '>')
		i = set_append(shell, new_token, input, i);
	else if (input[i] == '<' && input[i + 1] == '<')
		i = set_hered(shell, new_token, input, i);
	else
		i = set_simple(shell, new_token, input, i);
	
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

int	handle_pipe(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_pipe");
	
	new_token->value = ft_strdup("|");
	if (!new_token->value)
		exit_failure(shell, "handle_pipe_1");
	
	new_token->type = PIPE;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i++;
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

int	handle_quotes(t_shell *shell, char *input, int i)
{
	// Por enquanto, vamos tratar quotes como words normais
	// Isso será refinado quando implementarmos expansão
	return (handle_word_token(shell, input, i));
}