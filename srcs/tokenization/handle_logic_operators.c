/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logic_operators.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:18:23 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/09 09:18:23 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


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

/**
 * validate_logical_context - Valida contexto dos operadores lógicos
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * @operator: tipo do operador (AND_IF ou OR)
 * 
 * Verifica se o contexto do operador lógico é válido:
 * - Deve ter comandos antes e depois
 * - Não pode estar no início ou fim
 * 
 * Return: true se o contexto é válido
 */
bool	validate_logical_context(t_shell *shell, char *input, int i, int operator)
{
	int	j;
	
	(void)shell; // Silenciar warning
	(void)operator; // Para futuras validações específicas
	
	// Verifica se há conteúdo antes do operador
	j = i - 1;
	while (j >= 0 && ft_isspace(input[j]))
		j--;
	if (j < 0)
		return (false);
	
	// Verifica se há conteúdo depois do operador
	j = i + 2; // +2 porque são operadores de 2 caracteres
	while (input[j] && ft_isspace(input[j]))
		j++;
	if (!input[j])
		return (false);
	
	return (true);
}