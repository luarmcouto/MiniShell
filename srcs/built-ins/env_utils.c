/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * sh_get_env - Busca valor de variável de ambiente
 * @envp: lista de variáveis de ambiente
 * @value: nome da variável a buscar
 * 
 * Procura por uma variável específica na lista de ambiente.
 * 
 * Return: ponteiro para o conteúdo da variável ou NULL
 */
char	*sh_get_env(t_list *envp, const char *value)
{
	t_list	*current;
	t_env	*env_var;
	size_t	len;

	if (!envp || !value)
		return (NULL);
	len = ft_strlen(value);
	current = envp;
	while (current)
	{
		env_var = (t_env *)current->content;
		if (env_var && env_var->value)
		{
			if (ft_strncmp(env_var->value, value, len) == 0
				&& env_var->value[len] == '=')
				return (env_var->content);
		}
		current = current->next;
	}
	return (NULL);
}

/**
 * exec_parent_builtin - Executa built-ins no processo pai
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução
 * 
 * Executa built-ins que precisam afetar o ambiente do shell.
 * Implementação básica para os built-ins essenciais.
 * 
 * Return: código de saída do comando
 */
int	exec_parent_builtin(t_shell *shell, t_exec *exec_node)
{
	char	*cmd;

	cmd = exec_node->argv[0];
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(shell, exec_node));
	if (!ft_strcmp(cmd, "export"))
	{
		ft_export(shell, exec_node->argv);
		return (exit_code(-1));
	}
	if (!ft_strcmp(cmd, "unset"))
		return ((ft_unset(shell, exec_node->argv)), 0);
	if (!ft_strcmp(cmd, "exit"))
	{
		ft_putstr_fd("exit\n", 2);
		return (ft_exit(shell, exec_node), 0);
	}
	return (1);
}

/**
 * env_list - Cria lista de variáveis de ambiente
 * @shell: estrutura principal do shell
 * @envp: array de strings do ambiente
 * 
 * Converte o array de ambiente em uma lista ligada
 * de estruturas t_env para manipulação interna.
 * 
 * Return: NULL (atualiza shell->envp diretamente)
 */
t_list	*env_list(t_shell *shell, char **envp)
{
	t_env	*content;
	int		i;

	shell->envp = NULL;
	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		content = create_node_env(shell, &envp[i]);
		if (!content)
			exit_failure(shell, "env_list");
		ft_lstadd_back(&shell->envp, ft_lstnew(content));
		i++;
	}
	return (NULL);
}

/**
 * val_size - Calcula tamanho da parte do nome da variável
 * @env: string de ambiente no formato "NAME=value"
 * 
 * Calcula o tamanho da parte antes do '=' (incluindo o '=').
 * 
 * Return: tamanho da parte "NAME=" 
 */
int	val_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	return (i);
}

/**
 * content_size - Calcula tamanho da parte do valor da variável
 * @env: string de ambiente no formato "NAME=value"
 * 
 * Calcula o tamanho da parte depois do '=' (somente o valor).
 * 
 * Return: tamanho da parte "value"
 */
int	content_size(char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[j] && env[j] != '\0')
		j++;
	return (j - i);
}

/**
 * get_value - Extrai parte do nome da variável
 * @shell: estrutura principal do shell
 * @env: string de ambiente no formato "NAME=value"
 * 
 * Extrai e aloca a parte "NAME=" de uma string de ambiente.
 * 
 * Return: string alocada com "NAME="
 */
char	*get_value(t_shell *shell, char *env)
{
	char	*value;

	value = malloc(sizeof(char) * (val_size(env) + 1));
	if (!value)
		exit_failure(shell, "env_value");
	ft_strlcpy(value, env, val_size(env) + 1);
	return (value);
}

/**
 * get_content - Extrai parte do valor da variável
 * @shell: estrutura principal do shell
 * @env: string de ambiente no formato "NAME=value"
 * 
 * Extrai e aloca a parte "value" de uma string de ambiente.
 * 
 * Return: string alocada com "value"
 */
char	*get_content(t_shell *shell, char *env)
{
	char	*value;

	value = malloc(sizeof(char) * (content_size(env) + 1));
	if (!value)
		exit_failure(shell, "env_value");
	ft_strlcpy(value, env + val_size(env), content_size(env));
	return (value);
}

/**
 * create_node_env - Cria nó de variável de ambiente
 * @shell: estrutura principal do shell
 * @envp: ponteiro para string de ambiente
 * 
 * Cria uma estrutura t_env a partir de uma string
 * no formato "NAME=value".
 * 
 * Return: ponteiro para estrutura t_env criada
 */
t_env	*create_node_env(t_shell *shell, char **envp)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_failure(shell, "create_node_env");
	node->value = get_value(shell, *envp);
	node->content = get_content(shell, *envp);
	node->is_export = true;
	node->printed = false;
	return (node);
}