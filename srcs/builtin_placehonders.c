/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_placehonders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 20:07:29 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * is_builtin_command - Verifica se comando é um builtin
 * @command: nome do comando a verificar
 * 
 * Implementação real da função que estava como placeholder.
 * Usa a mesma lógica da função is_builtin() existente.
 * 
 * Return: 1 se é builtin, 0 se não é
 */
int	is_builtin_command(const char *command)
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
 * is_shell_builtin - Verifica se é builtin que deve rodar no processo pai
 * @exec_node: nó de execução com informações do comando
 * 
 * Implementação real baseada na função is_parent_builtin() existente.
 * Builtins como exit, cd, export, unset devem rodar no processo pai
 * para afetar o ambiente do shell principal.
 * 
 * Return: 1 se deve rodar no pai, 0 se pode rodar em processo filho
 */
int	is_shell_builtin(t_exec *exec_node)
{
	char	*cmd;

	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (0);

	cmd = exec_node->argv[0];

	// Builtins que DEVEM rodar no processo pai
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);

	return (0);
}

/**
 * execute_regular_builtin - Executa builtins que podem rodar em processo filho
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com informações do comando
 * 
 * Implementação real baseada na função exec_builtin() existente.
 * Executa builtins como echo, pwd, env que não precisam afetar
 * o ambiente do shell principal.
 * 
 * Return: código de saída do comando
 */
int	execute_regular_builtin(t_shell *shell, t_exec *exec_node)
{
	char	*cmd;
	
	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (1);
	exec_node->argv = expand_argv(shell, exec_node->argv);
	cmd = exec_node->argv[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(exec_node));	
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(), 0);	
	if (ft_strcmp(cmd, "env") == 0)
		return (print_env_lst(shell->envp), 0);	
	if (ft_strcmp(cmd, "export") == 0 && !exec_node->argv[1])
		return (builtin_export(shell, exec_node->argv), 0);
	return (1);
}

/**
 * execute_shell_builtin - Executa builtins que devem rodar no processo pai
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com informações do comando
 * 
 * Implementação real baseada na função exec_parent_builtin() existente.
 * Executa builtins que precisam modificar o ambiente do shell principal.
 * 
 * Return: código de saída do comando
 */
int	execute_shell_builtin(t_shell *shell, t_exec *exec_node)
{
	char	*cmd;

	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (1);

	cmd = exec_node->argv[0];

	if (ft_strcmp(cmd, "exit") == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_exit(shell, exec_node);
		return (0);  // Normalmente não chega aqui pois ft_exit faz exit()
	}

	if (ft_strcmp(cmd, "export") == 0)
	{
		builtin_export(shell, exec_node->argv);
		return (exit_code(-1));  // Retorna o exit code atual
	}

	if (ft_strcmp(cmd, "unset") == 0)
	{
		builtin_unset(shell, exec_node->argv);
		return (0);
	}

	if (ft_strcmp(cmd, "cd") == 0)
	{
		return (ft_cd(shell, exec_node));
	}

	// Se chegou até aqui, comando não reconhecido
	return (1);
}

/**
 * process_builtins - Processa comando builtin, decidindo onde executar
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com informações do comando
 * 
 * Implementação real baseada na função handle_builtins() existente.
 * Decide se o builtin deve rodar no processo pai ou filho e executa.
 * 
 * Return: código de saída do comando
 */
int	process_builtins(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (1);

	// Verifica se é um builtin que deve rodar no processo pai
	if (is_shell_builtin(exec_node))
	{
		return (execute_shell_builtin(shell, exec_node));
	}
	else
	{
		// É um builtin que pode rodar em processo filho
		return (execute_regular_builtin(shell, exec_node));
	}
}