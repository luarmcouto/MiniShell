/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:24:08 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/30 15:24:08 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * in_quotes - Verifica se posição está dentro de aspas duplas
 * @input: string de entrada
 * @i: posição a verificar
 * 
 * Função simples para verificar aspas duplas
 * Será expandida futuramente para verificação mais robusta
 * 
 * Return: true se está em aspas duplas
 */
bool	in_quotes(char *input, int i)
{
	if (input[i] == '"')
		return (true);
	return (false);
}

/**
 * set_simple - Configura token de redirecionamento simples (< ou >)
 * @shell: estrutura principal do shell
 * @new_token: token a ser configurado
 * @input: string de entrada
 * @i: posição atual
 * 
 * Return: nova posição após processar < ou >
 */
int	set_simple(t_shell *shell, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 1);
	if (!new_token->value)
		exit_failure(shell, "set_simple");
	
	if (input[i] == '<')
		new_token->type = INFILE;
	else
		new_token->type = OUTFILE;
	
	return (i + 1);
}

/**
 * is_expandable - Verifica se token precisa de expansão de variáveis
 * @token: string do token a verificar
 * 
 * Verifica se a string contém:
 * - $ seguido de caracteres alfanuméricos (variáveis)
 * - $? (exit status)
 * 
 * Considera contexto de aspas:
 * - Em aspas simples: não expande
 * - Em aspas duplas: expande
 * - Sem aspas: expande
 * 
 * Return: true se precisa de expansão
 */
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
		if (token[i] == '\'' && (token[i + 1] == '?'
				|| ft_isalnum(token[i + 1])))
			return (true);
		if (!in_quotes && (ft_isspace(token[i]) || ft_ismeta(token, i)))
			return (false);
		i++;
	}
	return (false);
}

/**
 * is_meta_operator - Verifica se é operador de múltiplos caracteres
 * @input: string de entrada
 * @i: posição atual
 * 
 * Verifica operadores de 2 caracteres:
 * - && (AND_IF)
 * - || (OR)
 * - >> (APPEND)
 * - << (HEREDOC)
 * 
 * Return: número de caracteres do operador (0, 1 ou 2)
 */
int	is_meta_operator(char *input, int i)
{
	if (!input || i < 0)
		return (0);
	
	// Operadores de 2 caracteres
	if (input[i] && input[i + 1])
	{
		if ((input[i] == '&' && input[i + 1] == '&') ||
			(input[i] == '|' && input[i + 1] == '|') ||
			(input[i] == '>' && input[i + 1] == '>') ||
			(input[i] == '<' && input[i + 1] == '<'))
			return (2);
	}
	
	// Operadores de 1 caractere
	if (input[i] == '|' || input[i] == '<' || input[i] == '>' ||
		input[i] == '(' || input[i] == ')')
		return (1);
	
	return (0);
}

/**
 * skip_whitespace - Pula espaços em branco
 * @input: string de entrada
 * @i: posição atual
 * 
 * Utilitário para pular todos os tipos de espaços em branco
 * 
 * Return: nova posição após espaços
 */
int	skip_whitespace(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

/**
 * find_quote_end - Encontra aspas de fechamento
 * @input: string de entrada
 * @i: posição da aspas de abertura
 * 
 * Encontra aspas de fechamento correspondente
 * 
 * Return: posição da aspas de fechamento ou -1 se não encontrada
 */
int	find_quote_end(char *input, int i)
{
	char	quote;
	
	if (!ft_isquote(input[i]))
		return (-1);
	
	quote = input[i];
	i++; // Pula aspas de abertura
	
	while (input[i])
	{
		if (input[i] == quote)
			return (i);
		i++;
	}
	
	return (-1); // Aspas não fechadas
}