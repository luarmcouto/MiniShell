/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:20:56 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/30 15:20:56 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * handle_pipe - Processa tokens de pipe
 * @shell: estrutura principal do shell
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Cria token para pipe (|) que conecta comandos
 * 
 * Return: nova posição no input após processar o pipe
 */
int	handle_pipe(t_shell *shell, char *input, int i)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "handle_pipe");
	
	new_token->value = ft_strdup("|");
	if (!new_token->value)
		exit_failure(shell, "handle_pipe_value");
	
	new_token->type = PIPE;
	new_token->state = GENERAL;
	ft_lstadd_back(&shell->token_lst, ft_lstnew(new_token));
	
	i++; // Avança uma posição (pipe é um caractere)
	
	// Pula espaços após o pipe
	while (input[i] && ft_isspace(input[i]))
		i++;
	
	return (i);
}

/**
 * is_valid_pipe_context - Verifica se o contexto do pipe é válido
 * @shell: estrutura principal do shell (não utilizado por enquanto)
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Validações:
 * - Não pode ser o primeiro caractere
 * - Não pode ser o último caractere
 * - Deve ter comandos antes e depois
 * 
 * Return: true se o contexto é válido, false caso contrário
 */
bool	is_valid_pipe_context(t_shell *shell, char *input, int i)
{
	int	j;
	
	(void)shell; // Silenciar warning de parâmetro não usado
	
	// Pipe no início da string é inválido
	if (i == 0)
		return (false);
	
	// Verifica se há conteúdo antes do pipe
	j = i - 1;
	while (j >= 0 && ft_isspace(input[j]))
		j--;
	if (j < 0)
		return (false);
	
	// Verifica se há conteúdo depois do pipe
	j = i + 1;
	while (input[j] && ft_isspace(input[j]))
		j++;
	if (!input[j])
		return (false);
	
	return (true);
}