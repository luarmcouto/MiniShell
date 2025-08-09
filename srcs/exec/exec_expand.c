/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:57:41 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/02 09:57:41 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * expand_argv - Expande variáveis em array de argumentos
 * @shell: estrutura principal do shell
 * @argv: array de argumentos para expandir
 * 
 * Return: novo array com variáveis expandidas
 */
char	**expand_argv(t_shell *shell, char **argv)
{
	char	**new_argv;
	char	*expanded;
	int		i;
	int		j;

	if (!argv)
		return (NULL);
	
	// Conta argumentos
	i = 0;
	while (argv && argv[i])
		i++;
	
	// Aloca novo array
	new_argv = ft_calloc(i + 1, sizeof(char *));
	if (!new_argv)
		exit_failure(shell, "expand_argv");
	
	// Expande cada argumento
	i = 0;
	j = 0;
	while (argv && argv[i])
	{
		if (is_expandable(argv[i]))
		{
			expanded = handle_expand(shell, argv[i], 0);
			if (expanded && ft_strlen(expanded) > 0)
				new_argv[j++] = expanded;
			else if (expanded)
				free(expanded);
		}
		else
		{
			new_argv[j++] = ft_strdup(argv[i]);
		}
		i++;
	}
	
	// Libera array original (não libera strings pois são tokens)
	free(argv);
	return (new_argv);
}

/**
 * free_expand - Libera array de strings expandidas
 * @argv: array para liberar
 */
void	free_expand(char **argv)
{
	int	i;

	if (!argv)
		return ;
	
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/**
 * f - Função de expansão simplificada
 * @shell: estrutura principal do shell
 * @input: string para expandir
 * 
 * Return: string expandida ou NULL se vazia
 */
char	*f(t_shell *shell, char *input)
{
	char	*str;
	int		i;

	if (!input)
		return (NULL);
	
	str = ft_strdup("");
	if (!str)
		exit_failure(shell, "f_expand");
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' || ft_isquote(input[i]))
		{
			// TODO: Implementar expansão completa na semana 2
			// Por enquanto, copia o caractere
			str = ft_strjoin_char(str, input[i]);
			i++;
		}
		else
		{
			while (input[i] && (input[i] != '$' && input[i] != '"'))
			{
				str = ft_strjoin_char(str, input[i]);
				i++;
			}
		}
		
		if (ft_isspace(input[i]) || ft_ismeta(input, i))
			break ;
	}
	
	// Se string vazia e começou com $, retorna NULL
	if (ft_strlen(str) == 0 && input[0] == '$')
	{
		free(str);
		return (NULL);
	}
	
	return (str);
}
