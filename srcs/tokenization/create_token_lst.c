/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:22:40 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/30 15:22:40 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO: diminuir linhas.

/**
 * tokenize_input - Função principal de tokenização
 * @shell: estrutura principal do shell
 * @input: string de entrada do usuário
 * 
 * Percorre a string de entrada e identifica diferentes tipos de tokens:
 * - Operadores lógicos (&&, ||)
 * - Pipes (|)
 * - Parênteses (, )
 * - Redirecionamentos (<, >, >>, <<)
 * - Palavras e comandos
 * 
 * Cada tipo é processado por seu handler específico
 */
void	tokenize_input(t_shell *shell, char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		// Pula espaços em branco
		if (ft_isspace(input[i]))
		{
			while (ft_isspace(input[i]))
				i++;
			continue;
		}
		
		// Verifica operadores lógicos primeiro (&&, ||)
		if (input[i] == '&' && input[i + 1] == '&')
			i = handle_andif(shell, input, i);
		else if (input[i] == '|' && input[i + 1] == '|')
			i = handle_or(shell, input, i);
		// Pipe simples (|)
		else if (input[i] == '|')
			i = handle_pipe(shell, input, i);
		// Parênteses (, )
		else if (input[i] == '(' || input[i] == ')')
			i = handle_parenthesis(shell, input, i);
		// Redirecionamentos (<, >, >>, <<)
		else if (input[i] == '>' || input[i] == '<')
			i = handle_redir(shell, input, i);
		// Palavras, comandos e argumentos
		else
			i = handle_word_token(shell, input, i);
		
		// Atualiza posições dos tokens
		set_token_pos(shell->token_lst);
	}
}

/**
 * handle_word_token - Processa tokens de palavra/comando
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Extrai palavras, comandos e argumentos da entrada.
 * Lida com aspas simples e duplas, preservando conteúdo
 * e mantendo informação sobre o tipo de aspas usado.
 * 
 * Return: nova posição no input após processar a palavra
 */
int	handle_word_token(t_shell *shell, char *input, int i)
{
	t_token	*new_token;
	char	*str;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_word_token");
	
	str = ft_strdup(""); // Inicializa string vazia
	if (!str)
		exit_failure(shell, "handle_word_token_str");
	
	// Processa caracteres até encontrar delimitador
	while (input[i] && !ft_isspace(input[i]) && !ft_ismeta(input, i))
	{
		i = join_strs(shell, &str, input, i);
	}
	
	new_token->value = str;
	new_token->type = WORD;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	return (i);
}

/**
 * handle_quotes - Processa especificamente tokens com aspas
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Função especializada para processar strings que começam com aspas.
 * Define o estado do token baseado no tipo de aspas:
 * - IN_SQUOTES para aspas simples
 * - IN_DQUOTES para aspas duplas
 * 
 * Return: nova posição no input após processar as aspas
 */
int	handle_quotes(t_shell *shell, char *input, int i)
{
	t_token		*new_token;
	const char	quote = input[i];
	char		*str;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_quotes");
	
	str = ft_strdup("");
	if (!str)
		exit_failure(shell, "handle_quotes_str");
	
	// Processa conteúdo incluindo aspas
	while (input[i] && !ft_isspace(input[i]) && !ft_ismeta(input, i))
	{
		i = join_strs(shell, &str, input, i);
	}
	
	new_token->value = str;
	new_token->type = WORD;
	
	// Define estado baseado no tipo de aspas
	if (quote == '"')
		new_token->state = IN_DQUOTES;
	else if (quote == '\'')
		new_token->state = IN_SQUOTES;
	else
		new_token->state = GENERAL;
	
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	return (i);
}
