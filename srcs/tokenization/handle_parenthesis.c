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

/**
 * handle_parenthesis - Processa tokens de parênteses para agrupamento
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Cria tokens para parênteses ( ) que controlam precedência
 * de operadores lógicos && e ||. Valida balanceamento.
 * 
 * Return: nova posição no input após processar o parênteses
 */
int	handle_parenthesis(t_shell *shell, char *input, int i)
{
	static bool	valid = false;
	int			start;
	char		*subs;

	// Se encontrou parênteses de fechamento
	if (input[i] == ')')
	{
		i = handle_closing(shell, input, i, valid);
		if (i != -1)
			return (i);
	}
	
	// Processa parênteses de abertura
	start = i;
	i = check_balance(input, i);
	
	// Extrai substring dentro dos parênteses para validação
	subs = ft_substr(&input[start + 1], 0, i - start - 1);
	valid = validate_subs(subs);
	free(subs);
	
	// Processa abertura com validação
	i = handle_opening(shell, input, start, valid);
	if (i != -1)
		return (i);
	
	// Ajusta posição inicial
	if (input[start] && input[start] == '(')
		start++;
	while (ft_isspace(input[start]))
		start++;
	
	return (start);
}

/**
 * handle_closing - Processa parênteses de fechamento
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * @valid: se o conteúdo dos parênteses é válido
 * 
 * Cria token para ) apenas se o conteúdo for válido
 * 
 * Return: nova posição no input
 */
int	handle_closing(t_shell *shell, char *input, int i, bool valid)
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
			exit_failure(shell, "handle_closing");
		
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
	return (-1);
}

/**
 * validate_subs - Valida se substring contém operadores válidos
 * @subs: substring a validar
 * 
 * Verifica se há operadores lógicos | ou & dentro dos parênteses
 * 
 * Return: true se válido
 */
bool	validate_subs(char *subs)
{
	char	*tokens;
	int		j;
	int		i;

	tokens = "|&";
	j = 0;
	i = 0;
	
	if (!subs || i < 0)
		return (false);
	
	while (subs[i])
	{
		j = 0;
		while (tokens[j])
		{
			if (subs[i] && subs[i] == tokens[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

/**
 * handle_opening - Processa parênteses de abertura
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * @valid: se o conteúdo é válido
 * 
 * Cria token para ( ou ) baseado na validação
 * 
 * Return: nova posição no input
 */
int	handle_opening(t_shell *shell, char *input, int i, bool valid)
{
	t_token	*new_token;
	char	*str;

	if (valid)
	{
		if (input[i] == '(')
			str = ft_strdup("(");
		if (input[i] == ')')
			str = ft_strdup(")");
		
		i++;
		if (!str)
			exit_failure(shell, "handle_opening");
		
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			exit_failure(shell, "handle_opening_token");
		
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

/**
 * jump_spaces - Pula espaços em branco
 * @input: string de entrada
 * @i: posição atual
 * 
 * Return: nova posição após espaços
 */
int	jump_spaces(char *input, int i)
{
	i++;
	while (ft_isspace(input[i]))
		i++;
	return (i);
}