/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:55:21 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/02 09:55:21 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: diminuir número de funções.

#include <minishell.h>

/**
 * expand_exit_status - Expande $? para exit status
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * 
 * Converte o código de saída atual para string
 * e adiciona ao resultado da expansão
 */
void	expand_exit_status(t_shell *shell, char **str)
{
	char	*exit_code_str;
	char	*tmp;
	
	exit_code_str = ft_itoa(exit_code(-1));
	if (!exit_code_str)
		exit_failure(shell, "expand_exit_status");
	
	tmp = *str;
	*str = ft_strjoin(*str, exit_code_str);
	free(tmp);
	free(exit_code_str);
	
	if (!*str)
		exit_failure(shell, "expand_exit_status_join");
}

/**
 * expand_pid - Expande $$ para PID do processo
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * 
 * Adiciona o PID do processo atual à string resultado
 * Usado para expansão de $$
 */
void	expand_pid(t_shell *shell, char **str)
{
	char	*pid_str;
	char	*tmp;
	pid_t	current_pid;
	
	current_pid = getpid();
	pid_str = ft_itoa((int)current_pid);
	if (!pid_str)
		exit_failure(shell, "expand_pid");
	
	tmp = *str;
	*str = ft_strjoin(*str, pid_str);
	free(tmp);
	free(pid_str);
	
	if (!*str)
		exit_failure(shell, "expand_pid_join");
}

/**
 * create_token - Cria um novo token
 * @shell: estrutura principal do shell
 * @str: string do token
 * 
 * Cria e inicializa um novo token com a string fornecida
 * Define tipo como WORD e estado apropriado
 * 
 * Return: ponteiro para novo token ou exit em caso de erro
 */
t_token	*create_token(t_shell *shell, char *str)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit_failure(shell, "create_token");
	
	new_token->value = str;
	new_token->type = WORD;
	new_token->state = GENERAL;
	
	// Se string vazia, marca como EXPAND para possível remoção
	if (!ft_strcmp(str, ""))
		new_token->state = EXPAND;
	
	return (new_token);
}

/**
 * is_valid_var_char - Verifica se caractere é válido para nome de variável
 * @c: caractere a verificar
 * 
 * Caracteres válidos para nomes de variáveis:
 * - Letras (a-z, A-Z)
 * - Números (0-9)
 * - Underscore (_)
 * 
 * Return: true se válido, false caso contrário
 */
bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * is_valid_var_start - Verifica se caractere pode iniciar nome de variável
 * @c: caractere a verificar
 * 
 * Primeiro caractere de variável deve ser:
 * - Letra (a-z, A-Z)
 * - Underscore (_)
 * 
 * Return: true se válido, false caso contrário
 */
bool	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

/**
 * should_expand - Verifica se token precisa de expansão
 * @token: string do token para verificar
 * 
 * Verifica se a string contém:
 * - $ seguido de caracteres válidos
 * - $? para exit status
 * - $$ para PID
 * 
 * Considera contexto de aspas (simples não expandem)
 * 
 * Return: true se precisa expansão, false caso contrário
 */
bool	should_expand(char *token)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	if (!token)
		return (false);
	
	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	
	while (token[i])
	{
		// Atualiza estado das aspas
		if (token[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (token[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		
		// Verifica expansão (não em aspas simples)
		if (token[i] == '$' && !in_single_quotes)
		{
			// $? ou $$
			if (token[i + 1] == '?' || token[i + 1] == '$')
				return (true);
			// $VAR_NAME
			if (is_valid_var_start(token[i + 1]))
				return (true);
		}
		
		i++;
	}
	
	return (false);
}

/**
 * count_expansion_parts - Conta partes após expansão
 * @expanded: string expandida
 * 
 * Conta quantas palavras separadas por espaços
 * resultaram da expansão de uma variável
 * 
 * Return: número de partes
 */
int	count_expansion_parts(char *expanded)
{
	int		count;
	int		i;
	bool	in_word;

	if (!expanded || !*expanded)
		return (0);
	
	count = 0;
	i = 0;
	in_word = false;
	
	while (expanded[i])
	{
		if (!ft_isspace(expanded[i]))
		{
			if (!in_word)
			{
				count++;
				in_word = true;
			}
		}
		else
		{
			in_word = false;
		}
		i++;
	}
	
	return (count);
}

/**
 * split_expansion - Divide expansão em palavras separadas
 * @shell: estrutura principal do shell
 * @expanded: string expandida
 * 
 * Divide uma string expandida em palavras separadas
 * baseadas em espaços (como bash faz)
 * 
 * Return: array de strings ou NULL se erro
 */
char	**split_expansion(t_shell *shell, char *expanded)
{
	char	**parts;
	int		word_count;
	int		i;
	int		j;
	int		start;
	
	if (!expanded)
		return (NULL);
	
	// Conta número de palavras
	word_count = count_expansion_parts(expanded);
	if (word_count == 0)
		return (NULL);
	
	// Aloca array
	parts = ft_calloc(word_count + 1, sizeof(char *));
	if (!parts)
		exit_failure(shell, "split_expansion");
	
	// Extrai cada palavra
	i = 0;
	j = 0;
	while (expanded[i] && j < word_count)
	{
		// Pula espaços
		while (expanded[i] && ft_isspace(expanded[i]))
			i++;
		
		if (!expanded[i])
			break;
		
		// Marca início da palavra
		start = i;
		
		// Encontra fim da palavra
		while (expanded[i] && !ft_isspace(expanded[i]))
			i++;
		
		// Extrai palavra
		parts[j] = ft_substr(expanded, start, i - start);
		if (!parts[j])
		{
			// Limpa em caso de erro
			while (j > 0)
				free(parts[--j]);
			free(parts);
			exit_failure(shell, "split_expansion_substr");
		}
		j++;
	}
	
	return (parts);
}