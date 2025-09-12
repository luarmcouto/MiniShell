/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:50:04 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:50:04 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * expand_heredoc_line - Expande variáveis em linha do heredoc
 * @shell: estrutura principal
 * @line: linha original do heredoc
 * 
 * Expande variáveis de ambiente ($VAR, ${VAR}, $?) na linha
 * Return: linha expandida (deve ser liberada)
 */
char	*expand_heredoc_line(t_shell *shell, char *line)
{
	char	*result;
	char	*temp;
	int		i;

	if (!line)
		return (ft_strdup(""));
		
	result = ft_strdup("");
	if (!result)
		exit_failure(shell, "expand_heredoc_line");
		
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			// Adiciona texto antes do $
			if (i > 0)
			{
				temp = ft_substr(line, 0, i);
				result = ft_strjoin_free(result, temp);
				free(temp);
			}
			
			// Expande a variável
			i = expand_variable_in_heredoc(shell, &result, line, i);
			
			// Continue com o resto da linha
			if (line[i])
			{
				temp = expand_heredoc_line(shell, &line[i]);
				result = ft_strjoin_free(result, temp);
				free(temp);
			}
			break;
		}
		i++;
	}
	
	// Se não havia $ na linha, apenas duplica
	if (i == (int)ft_strlen(line))
	{
		free(result);
		result = ft_strdup(line);
	}
	
	return (result);
}

/**
 * expand_variable_in_heredoc - Expande uma variável específica
 * @shell: estrutura principal
 * @result: string resultado sendo construída
 * @line: linha completa
 * @i: posição do $
 * 
 * Expande uma variável específica ($VAR, ${VAR}, $?, $$)
 * Return: nova posição após a variável
 */
int	expand_variable_in_heredoc(t_shell *shell, char **result, char *line, int i)
{
	char	*var_name;
	char	*var_value;
	int		var_start;

	i++; // Pula o $
	
	// Casos especiais
	if (line[i] == '?')
	{
		var_value = ft_itoa(shell->exit_code);
		*result = ft_strjoin_free(*result, var_value);
		free(var_value);
		return (i + 1);
	}
	
	if (line[i] == '$')
	{
		var_value = ft_itoa(getpid());
		*result = ft_strjoin_free(*result, var_value);
		free(var_value);
		return (i + 1);
	}
	
	// Variável com chaves ${VAR}
	if (line[i] == '{')
	{
		return (expand_braced_variable(shell, result, line, i));
	}
	
	// Variável simples $VAR
	var_start = i;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
		
	if (i == var_start)
	{
		// $ seguido de caractere inválido, mantém literal
		*result = ft_strjoin_free(*result, "$");
		return (var_start);
	}
	
	var_name = ft_substr(line, var_start, i - var_start);
	var_value = get_env_value(shell, var_name);
	
	if (var_value)
		*result = ft_strjoin_free(*result, var_value);
	
	free(var_name);
	return (i);
}

/**
 * expand_braced_variable - Expande variável com chaves ${VAR}
 * @shell: estrutura principal
 * @result: string resultado
 * @line: linha completa
 * @i: posição do {
 * 
 * Return: nova posição após }
 */
int	expand_braced_variable(t_shell *shell, char **result, char *line, int i)
{
	char	*var_name;
	char	*var_value;
	int		var_start;
	int		var_end;

	i++; // Pula o {
	var_start = i;
	
	// Encontra o }
	while (line[i] && line[i] != '}')
		i++;
		
	if (line[i] != '}')
	{
		// { sem }, trata como literal
		*result = ft_strjoin_free(*result, "${");
		return (var_start);
	}
	
	var_end = i;
	i++; // Pula o }
	
	if (var_end == var_start)
	{
		// ${} vazio
		*result = ft_strjoin_free(*result, "${}");
		return (i);
	}
	
	var_name = ft_substr(line, var_start, var_end - var_start);
	var_value = get_env_value(shell, var_name);
	
	if (var_value)
		*result = ft_strjoin_free(*result, var_value);
		
	free(var_name);
	return (i);
}

/**
 * get_env_value - Obtém valor de variável de ambiente
 * @shell: estrutura principal
 * @var_name: nome da variável
 * 
 * Return: valor da variável ou NULL se não existir
 */
char	*get_env_value(t_shell *shell, char *var_name)
{
	t_list	*current;
	char	*env_entry;
	char	*equal_pos;
	int		name_len;

	if (!var_name || !*var_name)
		return (NULL);
		
	name_len = ft_strlen(var_name);
	current = shell->envp;
	
	while (current)
	{
		env_entry = (char *)current->content;
		equal_pos = ft_strchr(env_entry, '=');
		
		if (equal_pos && (equal_pos - env_entry) == name_len &&
		    ft_strncmp(env_entry, var_name, name_len) == 0)
		{
			return (equal_pos + 1);
		}
		
		current = current->next;
	}
	
	return (NULL);
}

/**
 * validate_heredoc_expansion - Valida expansão no heredoc
 * @shell: estrutura principal
 * @line: linha a validar
 * 
 * Verifica se a expansão é válida e segura
 * Return: true se válida
 */
bool	validate_heredoc_expansion(t_shell *shell, char *line)
{
	int		i;
	int		brace_count;

	(void)shell; // Evita warning de parâmetro não usado
	
	if (!line)
		return (true);
		
	i = 0;
	brace_count = 0;
	
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '{')
		{
			i += 2;
			brace_count++;
			
			// Verifica se há } correspondente
			while (line[i] && line[i] != '}')
				i++;
				
			if (line[i] == '}')
			{
				brace_count--;
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	
	// Verifica se todas as chaves foram fechadas
	if (brace_count != 0)
	{
		ft_putstr_fd("minishell: warning: unclosed brace in heredoc\n", 2);
		return (false);
	}
	
	return (true);
}