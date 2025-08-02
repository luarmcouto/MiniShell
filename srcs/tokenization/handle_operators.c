/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:22:02 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/30 15:22:02 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * handle_andif - Processa operador lógico && (AND)
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Cria token para operador && que executa comando seguinte
 * apenas se o anterior teve sucesso (exit code 0)
 * 
 * Return: nova posição no input após processar o operador
 */
int	handle_andif(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_andif");
	
	new_token->value = ft_strdup("&&");
	if (!new_token->value)
		exit_failure(shell, "handle_andif_value");
	
	new_token->type = AND_IF;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i += 2; // Avança duas posições (&& são dois caracteres)
	
	// Pula espaços após o operador
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

/**
 * handle_or - Processa operador lógico || (OR)
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Cria token para operador || que executa comando seguinte
 * apenas se o anterior falhou (exit code != 0)
 * 
 * Return: nova posição no input após processar o operador
 */
int	handle_or(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_or");
	
	new_token->value = ft_strdup("||");
	if (!new_token->value)
		exit_failure(shell, "handle_or_value");
	
	new_token->type = OR;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i += 2; // Avança duas posições (|| são dois caracteres)
	
	// Pula espaços após o operador
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

/**
 * handle_parenthesis - Processa parênteses para agrupamento
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Cria tokens para parênteses ( ) que controlam precedência
 * de operadores lógicos && e ||
 * 
 * Return: nova posição no input após processar o parênteses
 */
int	handle_parenthesis(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_parenthesis");
	
	if (input[i] == '(')
		new_token->value = ft_strdup("(");
	else if (input[i] == ')')
		new_token->value = ft_strdup(")");
	
	if (!new_token->value)
		exit_failure(shell, "handle_parenthesis_value");
	
	new_token->type = PARENTHESIS;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i++; // Avança uma posição (parênteses é um caractere)
	
	// Pula espaços após o parênteses
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

/**
 * is_logical_operator - Verifica se é início de operador lógico
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Verifica se a posição atual é início de && ou ||
 * 
 * Return: tipo do operador ou 0 se não for operador
 */
int	is_logical_operator(char *input, int i)
{
	if (input[i] == '&' && input[i + 1] == '&')
		return (AND_IF);
	else if (input[i] == '|' && input[i + 1] == '|')
		return (OR);
	return (0);
}
