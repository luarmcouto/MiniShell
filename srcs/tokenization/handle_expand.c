/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:54:06 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/02 09:54:06 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: diminuir número de funções.

#include <minishell.h>

/**
 * handle_expand - Função principal de expansão de variáveis
 * @shell: estrutura principal do shell
 * @input: string de entrada para expansão
 * @i: posição inicial na string
 * 
 * Processa expansão de variáveis ($VAR, $?, $$) em uma string
 * Lida com diferentes contextos (aspas simples, duplas, sem aspas)
 * 
 * Return: string expandida ou NULL se erro/string vazia
 */
char	*handle_expand(t_shell *shell, char *input, int i)
{
	char	*str;

	if (!input)
		return (NULL);
	
	str = ft_strdup("");
	if (!str)
		exit_failure(shell, "handle_expand");
	
	while (input[i])
	{
		if (input[i] == '$' || ft_isquote(input[i]))
			i = process_expansion(shell, &str, input, i);
		else
			i = add_literal_chars(shell, &str, input, i);
		
		// Para de processar se encontrar delimitador
		if (input[i] && (ft_isspace(input[i]) || ft_ismeta(input, i)))
			break;
	}
	
	// Se string vazia e começou com $, retorna NULL
	if (ft_strlen(str) == 0 && input[0] == '$')
	{
		free(str);
		return (NULL);
	}
	
	return (str);
}

/**
 * process_expansion - Processa expansões e aspas
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Determina o tipo de expansão necessária:
 * - Variáveis sem aspas
 * - Variáveis em aspas duplas
 * - Conteúdo em aspas simples (sem expansão)
 * 
 * Return: nova posição na string
 */
int	process_expansion(t_shell *shell, char **str, char *input, int i)
{
	bool	in_double_quotes;

	in_double_quotes = false;
	
	while (input[i] && !ft_isspace(input[i]) && !ft_ismeta(input, i))
	{
		// Processa variáveis fora de aspas
		while (input[i] == '$')
			i = expand_unquoted(shell, str, input, i);
		
		// Gerencia estado de aspas duplas
		if (input[i] == '"')
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		
		// Processa conteúdo em aspas duplas
		while (input[i] && in_double_quotes)
		{
			while (input[i] && input[i] != '$' && input[i] != '"')
				*str = ft_strjoin_char(*str, input[i++]);
			
			if (input[i] == '$')
				i = expand_in_quotes(shell, str, input, i);
			else if (input[i] == '"')
			{
				in_double_quotes = false;
				i++;
			}
		}
		
		// Processa aspas simples (sem expansão)
		if (input[i] && input[i] == '\'')
			i = expand_single_quotes(shell, str, input, i);
		// Processa caracteres literais
		else if (input[i] && !ft_ismeta(input, i) && !ft_isspace(input[i]))
			*str = ft_strjoin_char(*str, input[i++]);
	}
	
	return (i);
}

/**
 * expand_unquoted - Expande variáveis fora de aspas
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual (caractere '$')
 * 
 * Expande variáveis em contexto sem aspas:
 * - $VAR_NAME
 * - $? (exit status)
 * - $$ (PID do processo)
 * 
 * Return: nova posição na string
 */
int	expand_unquoted(t_shell *shell, char **str, char *input, int i)
{
	int		start;
	char	*tmp;
	char	*var_name;
	char	*var_value;

	if (input[i] != '$')
		return (i);
	
	start = ++i; // Pula o '$'
	
	// Trata casos especiais
	if (input[i] == '?')
		return (expand_exit_status(shell, str), i + 1);
	if (input[i] == '$')
		return (expand_pid(shell, str), i + 1);
	
	// Coleta nome da variável
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_') 
		&& !ft_isspace(input[i]) && !ft_ismeta(input, i))
		i++;
	
	// Se não há nome após $, adiciona $ literal
	if (i == start)
	{
		*str = ft_strjoin_char(*str, '$');
		return (i);
	}
	
	// Extrai nome da variável
	var_name = ft_substr(input, start, i - start);
	if (!var_name)
		exit_failure(shell, "expand_unquoted");
	
	// Busca valor da variável
	var_value = sh_get_env(shell->envp, var_name);
	free(var_name);
	
	// Adiciona valor se encontrado
	if (var_value && ft_strlen(var_value) > 0)
	{
		tmp = *str;
		*str = ft_strjoin(*str, var_value);
		free(tmp);
		if (!*str)
			exit_failure(shell, "expand_unquoted_join");
	}
	
	return (i);
}

/**
 * expand_in_quotes - Expande variáveis dentro de aspas duplas
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual (caractere '$')
 * 
 * Similar a expand_unquoted mas para contexto de aspas duplas
 * Usa getenv() em vez de sh_get_env() por compatibilidade
 * 
 * Return: nova posição na string
 */
int	expand_in_quotes(t_shell *shell, char **str, char *input, int i)
{
	int		start;
	char	*tmp;
	char	*var_name;
	char	*var_value;

	if (input[i] != '$')
		return (i);
	
	start = ++i; // Pula o '$'
	
	// Trata casos especiais
	if (input[i] == '?')
		return (expand_exit_status(shell, str), i + 1);
	if (input[i] == '$')
		return (expand_pid(shell, str), i + 1);
	
	// Coleta nome da variável (para até aspas)
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_') 
		&& input[i] != '"')
		i++;
	
	// Se não há nome após $, adiciona $ literal
	if (i == start)
	{
		*str = ft_strjoin_char(*str, '$');
		return (i);
	}
	
	// Extrai nome da variável
	var_name = ft_substr(input, start, i - start);
	if (!var_name)
		exit_failure(shell, "expand_in_quotes");
	
	// Busca valor usando getenv para aspas duplas
	var_value = getenv(var_name);
	free(var_name);
	
	// Adiciona valor se encontrado
	if (var_value && ft_strlen(var_value) > 0)
	{
		tmp = *str;
		*str = ft_strjoin(*str, var_value);
		free(tmp);
		if (!*str)
			exit_failure(shell, "expand_in_quotes_join");
	}
	
	return (i);
}

/**
 * expand_single_quotes - Processa conteúdo de aspas simples
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual (caractere '\'')
 * 
 * Em aspas simples, NENHUMA expansão ocorre
 * Todos os caracteres são tratados literalmente
 * 
 * Return: nova posição na string
 */
int	expand_single_quotes(t_shell *shell, char **str, char *input, int i)
{
	int		start;
	char	*tmp;
	char	*literal_content;

	if (input[i] != '\'')
		return (i);
	
	start = ++i; // Pula aspas de abertura
	
	// Encontra aspas de fechamento
	while (input[i] && input[i] != '\'')
		i++;
	
	// Extrai conteúdo literal
	literal_content = ft_substr(input, start, i - start);
	if (!literal_content)
		exit_failure(shell, "expand_single_quotes");
	
	// Adiciona à string resultado
	tmp = *str;
	*str = ft_strjoin(*str, literal_content);
	free(tmp);
	free(literal_content);
	
	if (!*str)
		exit_failure(shell, "expand_single_quotes_join");
	
	if (input[i] == '\'')
		i++; // Pula aspas de fechamento
	
	return (i);
}

/**
 * add_literal_chars - Adiciona caracteres literais à string
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * @input: string de entrada
 * @i: posição atual na string
 * 
 * Adiciona caracteres que não precisam de expansão
 * Para quando encontra delimitadores
 * 
 * Return: nova posição na string
 */
int	add_literal_chars(t_shell *shell, char **str, char *input, int i)
{
	while (input[i] && input[i] != '$' && !ft_isquote(input[i]) 
		&& !ft_isspace(input[i]) && !ft_ismeta(input, i))
	{
		*str = ft_strjoin_char(*str, input[i]);
		if (!*str)
			exit_failure(shell, "add_literal_chars");
		i++;
	}
	
	return (i);
}