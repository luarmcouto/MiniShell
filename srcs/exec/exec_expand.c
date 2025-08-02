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

// TODO: diminuir número de funções.

#include <minishell.h>

/**
 * expand_argv - Expande array de argumentos
 * @shell: estrutura principal do shell
 * @argv: array de argumentos para expandir
 * 
 * Expande todas as variáveis em cada argumento
 * Remove argumentos que se tornam vazios após expansão
 * Divide argumentos que se tornam múltiplas palavras
 * 
 * Return: novo array expandido
 */
char	**expand_argv(t_shell *shell, char **argv)
{
	char	**new_argv;
	char	*expanded;
	int		i;
	int		j;

	if (!argv)
		return (NULL);
	
	i = 0;
	while (argv[i])
		i++;
	
	// Aloca array com espaço extra para expansões múltiplas
	new_argv = ft_calloc(i * 3 + 1, sizeof(char *));
	if (!new_argv)
		exit_failure(shell, "expand_argv");
	
	i = 0;
	j = 0;
	while (argv[i])
	{
		expanded = handle_expand(shell, argv[i], 0);
		
		// Se expansão resultou em string válida
		if (expanded && ft_strlen(expanded) > 0)
		{
			// Se contém espaços, divide em múltiplas palavras
			if (contains_spaces(expanded))
				j = add_split_args(shell, new_argv, expanded, j);
			else
			{
				new_argv[j] = expanded;
				j++;
			}
		}
		else if (expanded)
		{
			// String vazia - libera mas não adiciona
			free(expanded);
		}
		
		i++;
	}
	
	// Redimensiona array para tamanho exato
	new_argv = resize_argv(shell, new_argv, j);
	
	return (new_argv);
}

/**
 * contains_spaces - Verifica se string contém espaços
 * @str: string para verificar
 * 
 * Return: true se contém espaços, false caso contrário
 */
bool	contains_spaces(char *str)
{
	int	i;

	if (!str)
		return (false);
	
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (true);
		i++;
	}
	
	return (false);
}

/**
 * add_split_args - Adiciona argumentos divididos ao array
 * @shell: estrutura principal do shell
 * @argv: array de argumentos
 * @expanded: string expandida para dividir
 * @start_index: índice inicial para inserir
 * 
 * Divide string expandida por espaços e adiciona
 * cada parte como argumento separado
 * 
 * Return: próximo índice disponível
 */
int	add_split_args(t_shell *shell, char **argv, char *expanded, int start_index)
{
	char	**parts;
	int		i;
	int		current_index;

	parts = split_expansion(shell, expanded);
	if (!parts)
	{
		free(expanded);
		return (start_index);
	}
	
	current_index = start_index;
	i = 0;
	while (parts[i])
	{
		argv[current_index] = ft_strdup(parts[i]);
		if (!argv[current_index])
			exit_failure(shell, "add_split_args");
		current_index++;
		i++;
	}
	
	// Libera array temporário e string original
	ft_free_array(parts);
	free(expanded);
	
	return (current_index);
}

/**
 * resize_argv - Redimensiona array para tamanho exato
 * @shell: estrutura principal do shell
 * @argv: array original
 * @new_size: novo tamanho
 * 
 * Return: array redimensionado
 */
char	**resize_argv(t_shell *shell, char **argv, int new_size)
{
	char	**resized;
	int		i;

	resized = ft_calloc(new_size + 1, sizeof(char *));
	if (!resized)
		exit_failure(shell, "resize_argv");
	
	i = 0;
	while (i < new_size && argv[i])
	{
		resized[i] = argv[i];
		i++;
	}
	
	free(argv); // Só libera o array, não as strings
	return (resized);
}

/**
 * expand_filename - Expande filename para redirecionamentos
 * @shell: estrutura principal do shell
 * @filename: nome do arquivo para expandir
 * 
 * Expande variáveis em nomes de arquivos
 * Usado para redirecionamentos < > >> <<
 * 
 * Return: filename expandido ou NULL se erro
 */
char	*expand_filename(t_shell *shell, char *filename)
{
	char	*expanded;

	if (!filename)
		return (NULL);
	
	expanded = handle_expand(shell, filename, 0);
	
	// Filename não pode ser vazio ou conter múltiplas palavras
	if (!expanded || ft_strlen(expanded) == 0)
	{
		if (expanded)
			free(expanded);
		return (NULL);
	}
	
	// Se contém espaços, é ambíguo
	if (contains_spaces(expanded))
	{
		free(expanded);
		return (NULL);
	}
	
	return (expanded);
}

/**
 * expand_heredoc_line - Expande linha de heredoc
 * @shell: estrutura principal do shell
 * @line: linha para expandir
 * 
 * Expande variáveis em linhas de heredoc
 * Usado durante leitura de << EOF
 * 
 * Return: linha expandida
 */
char	*expand_heredoc_line(t_shell *shell, char *line)
{
	char	*expanded;

	if (!line)
		return (NULL);
	
	expanded = handle_expand(shell, line, 0);
	
	// Se expansão falha, retorna linha original
	if (!expanded)
	{
		expanded = ft_strdup(line);
		if (!expanded)
			exit_failure(shell, "expand_heredoc_line");
	}
	
	return (expanded);
}

/**
 * free_string_array - Libera array de strings
 * @array: array para liberar
 * 
 * Libera todas as strings do array e o próprio array
 */
void	free_string_array(char **array)
{
	ft_free_array(array);
}

/**
 * count_argv_size - Conta tamanho necessário para argv expandido
 * @shell: estrutura principal do shell
 * @argv: array original
 * 
 * Calcula quantos elementos o array terá após expansão
 * considerando que variáveis podem virar múltiplas palavras
 * 
 * Return: tamanho estimado
 */
int	count_argv_size(t_shell *shell, char **argv)
{
	int		total_size;
	int		i;
	char	*expanded;
	int		parts;

	if (!argv)
		return (0);
	
	total_size = 0;
	i = 0;
	while (argv[i])
	{
		if (should_expand(argv[i]))
		{
			expanded = handle_expand(shell, argv[i], 0);
			if (expanded)
			{
				parts = count_expansion_parts(expanded);
				total_size += parts;
				free(expanded);
			}
		}
		else
		{
			total_size++;
		}
		i++;
	}
	
	return (total_size);
}

/**
 * expand_single_arg - Expande um único argumento
 * @shell: estrutura principal do shell
 * @arg: argumento para expandir
 * 
 * Expande um argumento e retorna array com todas as partes
 * Se não há expansão, retorna array com argumento original
 * 
 * Return: array de strings expandidas
 */
char	**expand_single_arg(t_shell *shell, char *arg)
{
	char	**result;
	char	*expanded;

	if (!arg)
		return (NULL);
	
	if (!should_expand(arg))
	{
		// Sem expansão - retorna array com original
		result = ft_calloc(2, sizeof(char *));
		if (!result)
			exit_failure(shell, "expand_single_arg");
		result[0] = ft_strdup(arg);
		if (!result[0])
			exit_failure(shell, "expand_single_arg_dup");
		return (result);
	}
	
	expanded = handle_expand(shell, arg, 0);
	if (!expanded || ft_strlen(expanded) == 0)
	{
		// Expansão vazia - retorna array vazio
		if (expanded)
			free(expanded);
		result = ft_calloc(1, sizeof(char *));
		if (!result)
			exit_failure(shell, "expand_single_arg_empty");
		return (result);
	}
	
	// Divide por espaços se necessário
	if (contains_spaces(expanded))
	{
		result = split_expansion(shell, expanded);
		free(expanded);
	}
	else
	{
		result = ft_calloc(2, sizeof(char *));
		if (!result)
			exit_failure(shell, "expand_single_arg_single");
		result[0] = expanded;
	}
	
	return (result);
}
