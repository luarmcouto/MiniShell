/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:58:42 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:58:42 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * ft_strjoin_free - Junta duas strings e libera as originais
 * @s1: primeira string
 * @s2: segunda string
 * 
 * Return: nova string ou NULL se erro
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

/**
 * ft_isspace - Verifica se caractere é espaço em branco
 * @c: caractere a verificar
 * 
 * Verifica espaço, tab, newline, vertical tab, form feed, carriage return
 * 
 * Return: 1 se é espaço, 0 caso contrário
 */
int	ft_isspace(char c)
{
	return (c == ' '  ||  // espaço
			c == '\t' ||  // tabulação horizontal
			c == '\n' ||  // nova linha
			c == '\v' ||  // tabulação vertical
			c == '\f' ||  // form feed
			c == '\r');   // carriage return
}

/**
 * ft_strndup - Duplica n caracteres de uma string
 * @s: string fonte
 * @n: número de caracteres
 * 
 * Return: nova string alocada ou NULL se erro
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	
	return (dup);
}

/**
 * ft_array_len - Conta elementos em array de strings
 * @array: array a contar
 * 
 * Return: número de elementos (até NULL)
 */
int	ft_array_len(char **array)
{
	int	count;

	if (!array)
		return (0);
	
	count = 0;
	while (array[count])
		count++;
	
	return (count);
}

/**
 * ft_free_array - Libera array de strings
 * @array: array a liberar
 * 
 * Libera todas as strings e o array
 */
void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return;
	
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}