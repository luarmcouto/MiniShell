/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:21:32 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/30 15:21:32 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * join_strs - Processa e junta strings considerando aspas
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Determina se deve processar string com aspas ou sem aspas
 * e junta ao resultado final
 * 
 * Return: nova posição no input após processar a string
 */
int	join_strs(t_shell *shell, char **str, char *input, int i)
{
	if (ft_isquote(input[i]))
	{
		i = handle_quoted_str(shell, str, input, i);
	}
	else
	{
		i = handle_nonquoted_str(shell, str, input, i);
	}
	return (i);
}

/**
 * handle_quoted_str - Processa strings dentro de aspas
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Extrai conteúdo entre aspas (simples ou duplas) incluindo
 * as próprias aspas para preservar informação de tipo
 * 
 * Return: nova posição no input após processar a string
 */
int	handle_quoted_str(t_shell *shell, char **str, char *input, int i)
{
	char	*join;
	char	quote;
	int		start;
	char	*tmp;

	quote = input[i];  // Armazena tipo de aspas (' ou ")
	start = i;
	i++; // Pula aspas de abertura
	
	// Procura aspas de fechamento
	while (input[i] && input[i] != quote)
		i++;
	
	if (input[i] == quote)
		i++; // Inclui aspas de fechamento
	
	// Extrai substring incluindo as aspas
	join = ft_substr(input, start, i - start);
	if (!join)
		exit_failure(shell, "handle_quoted_str");
	
	// Junta à string resultado
	tmp = *str;
	*str = ft_strjoin(*str, join);
	free(tmp);
	free(join);
	
	if (!*str)
		exit_failure(shell, "handle_quoted_str_join");
	
	return (i);
}

/**
 * handle_nonquoted_str - Processa strings sem aspas
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Extrai sequência de caracteres até encontrar:
 * - Espaços
 * - Aspas
 * - Metacaracteres
 * 
 * Return: nova posição no input após processar a string
 */
int	handle_nonquoted_str(t_shell *shell, char **str, char *input, int i)
{
	char	*join;
	int		start;
	char	*tmp;

	start = i;
	
	// Avança até encontrar delimitador
	while (input[i] && !ft_isquote(input[i]) 
		&& !ft_isspace(input[i]) && !ft_ismeta(input, i))
		i++;
	
	// Extrai substring
	join = ft_substr(input, start, i - start);
	if (!join)
		exit_failure(shell, "handle_nonquoted_str");
	
	// Junta à string resultado
	tmp = *str;
	*str = ft_strjoin(*str, join);
	free(tmp);
	free(join);
	
	if (!*str)
		exit_failure(shell, "handle_nonquoted_str_join");
	
	return (i);
}

/**
 * ft_strjoin_char - Junta string com um caractere
 * @str: string original
 * @c: caractere a ser adicionado
 * 
 * Utilitário para adicionar um caractere ao final de uma string
 * Libera a string original
 * 
 * Return: nova string com caractere adicionado
 */
char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	
	free(str);
	return (new_str);
}
