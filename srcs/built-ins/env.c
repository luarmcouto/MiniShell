/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

// Função básica para criar lista de ambiente
t_list	*env_list(t_shell *shell_data, char **envp)
{
	t_list		*env_lst;
	t_env_var	*env_node;
	int			i;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		env_node = create_env_node(shell_data, &envp[i]);
		if (!env_node)
			exit_failure(shell_data, "env_list: node creation failed");
		ft_lstadd_back(&env_lst, ft_lstnew(env_node));
		i++;
	}
	return (env_lst);
}

// Criar nó de ambiente
t_env_var	*create_env_node(t_shell *shell_data, char **env_entry)
{
	t_env_var	*node;
	char		*equals_pos;

	node = malloc(sizeof(t_env_var));
	if (!node)
		return (NULL);
	equals_pos = ft_strchr(*env_entry, '=');
	if (equals_pos)
	{
		node->value = ft_strndup(*env_entry, equals_pos - *env_entry + 1);
		node->content = ft_strdup(equals_pos + 1);
	}
	else
	{
		node->value = ft_strjoin(*env_entry, "=");
		node->content = ft_strdup("");
	}
	node->is_export = true;
	node->printed = false;
	if (!node->value || !node->content)
	{
		free(node->value);
		free(node->content);
		free(node);
		exit_failure(shell_data, "create_env_node: allocation failed");
	}
	return (node);
}

// Extrair valor da variável de ambiente
char	*extract_value(t_shell *shell_data, char *env_str)
{
	char	*equals_pos;
	char	*result;

	equals_pos = ft_strchr(env_str, '=');
	if (!equals_pos)
		result = ft_strjoin(env_str, "=");
	else
		result = ft_strndup(env_str, equals_pos - env_str + 1);
	if (!result)
		exit_failure(shell_data, "extract_value: allocation failed");
	return (result);
}

// Extrair conteúdo da variável de ambiente  
char	*extract_content(t_shell *shell_data, char *env_str)
{
	char	*equals_pos;
	char	*result;

	equals_pos = ft_strchr(env_str, '=');
	if (!equals_pos)
		result = ft_strdup("");
	else
		result = ft_strdup(equals_pos + 1);
	if (!result)
		exit_failure(shell_data, "extract_content: allocation failed");
	return (result);
}

// Função de compatibilidade para criar lista de ambiente
t_list	*create_env_list(t_shell *shell_data, char **envp)
{
	return (env_list(shell_data, envp));
}