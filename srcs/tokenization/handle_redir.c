/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:20:10 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/30 15:20:10 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * handle_redir - Processa tokens de redirecionamento
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Identifica e cria tokens para redirecionamentos:
 * < (INFILE), > (OUTFILE), >> (APPEND), << (HEREDOC)
 * 
 * Return: nova posição no input após processar o redirecionamento
 */
int	handle_redir(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_redir");
	
	// Verifica se é redirecionamento duplo (>> ou <<)
	if (input[i] == '>' && input[i + 1] == '>')
		i = set_append(shell, new_token, input, i);
	else if (input[i] == '<' && input[i + 1] == '<')
		i = set_heredoc(shell, new_token, input, i);
	else
		i = set_simple_redir(shell, new_token, input, i);
	
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	// Pula espaços após o redirecionamento
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

/**
 * set_append - Configura token para append (>>)
 */
int	set_append(t_shell *shell, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 2);
	if (!new_token->value)
		exit_failure(shell, "set_append");
	new_token->type = APPEND;
	return (i + 2);
}

/**
 * set_heredoc - Configura token para heredoc (<<)
 */
int	set_heredoc(t_shell *shell, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 2);
	if (!new_token->value)
		exit_failure(shell, "set_heredoc");
	new_token->type = HEREDOC;
	return (i + 2);
}

/**
 * set_simple_redir - Configura token para redirecionamentos simples (< ou >)
 */
int	set_simple_redir(t_shell *shell, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 1);
	if (!new_token->value)
		exit_failure(shell, "set_simple_redir");
	
	if (input[i] == '<')
		new_token->type = INFILE;
	else if (input[i] == '>')
		new_token->type = OUTFILE;
	
	return (i + 1);
}

/**
 * validate_redir_syntax - Valida sintaxe dos redirecionamentos
 * @shell: estrutura principal
 * @input: string de entrada
 * @i: posição atual
 * 
 * Verifica se há arquivo após o operador de redirecionamento
 * Return: true se válido, false caso contrário
 */
bool	validate_redir_syntax(t_shell *shell, char *input, int i)
{
	// Pula o operador de redirecionamento
	if (input[i] == '>' || input[i] == '<')
	{
		i++;
		if (input[i] == '>' || input[i] == '<')
			i++;
	}
	
	// Pula espaços
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	// Verifica se há um nome de arquivo válido
	if (!input[i] || input[i] == '|' || input[i] == '>' || input[i] == '<' 
		|| input[i] == '&')
	{
		shell->exit_code = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (false);
	}
	
	return (true);
}