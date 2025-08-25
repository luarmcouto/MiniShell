/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/25 21:14:59 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * is_builtin - Verifica se comando é um built-in
 * @command: nome do comando
 * 
 * Verifica se o comando é um dos built-ins obrigatórios.
 * 
 * Return: 1 se é built-in, 0 caso contrário
 */
int	is_builtin(const char *command)
{
	const char	*builtins[8] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", NULL};
	int			i;

	if (!command)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp((char *)command, (char *)builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * is_parent_builtin - Verifica se é built-in do processo pai
 * @exec_node: nó de execução
 * 
 * Alguns built-ins devem executar no processo pai para
 * afetar o ambiente do shell (cd, export, unset, exit).
 * 
 * Return: 1 se deve executar no pai, 0 caso contrário
 */
int	is_parent_builtin(t_exec *exec_node)
{
	char	*cmd;

	cmd = NULL;
	if (exec_node->argv)
		cmd = exec_node->argv[0];
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

/**
 * exec_builtin - Executa built-ins que podem rodar em child
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução
 * 
 * Executa built-ins que não precisam afetar o ambiente do pai.
 * 
 * Return: código de saída do comando
 */
int	exec_builtin(t_shell *shell, t_exec *exec_node)
{
	char	*cmd;

	cmd = exec_node->argv[0];
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(exec_node));
	if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd(), 0);
	if (!ft_strcmp(cmd, "env"))
		return (print_env_lst(shell->envp), 0);
	if (!ft_strcmp(cmd, "export") && !exec_node->argv[1])
		return (ft_export(shell, exec_node->argv), 0);
	return (1);
}

/**
 * handle_builtins - Dispatcher principal dos built-ins
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução
 * 
 * Determina se comando deve executar no pai ou filho
 * e chama a função apropriada.
 * 
 * Return: código de saída do comando
 */
int	handle_builtins(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node || !exec_node->argv[0])
		return (1);
	if (is_parent_builtin(exec_node))
		return (exec_parent_builtin(shell, exec_node));
	return (exec_builtin(shell, exec_node));
}