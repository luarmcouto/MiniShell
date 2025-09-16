/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:15:33 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/16 19:17:56 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * is_builtin_command - Verifica se comando é um builtin
 * @command: nome do comando a verificar
 *
 * Return: 1 se for builtin, 0 caso contrário
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
 * is_parent_builtin - Verifica se builtin deve rodar no processo pai
 * @exec_node: nó de execução
 *
 * Builtins que modificam o ambiente do shell (cd, export, unset, exit)
 * devem rodar no processo pai. Outros podem rodar em processo filho.
 *
 * Return: 1 se deve rodar no processo pai, 0 caso contrário
 */
int	is_parent_builtin(t_exec *exec_node)
{
	char	*cmd;
	
	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (0);
	
	cmd = exec_node->argv[0];
	
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	
	return (0);
}

/**
 * exec_parent_builtin - Executa builtins que devem rodar no processo pai
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com informações do comando
 *
 * Return: código de saída do comando
 */
int	exec_parent_builtin(t_shell *shell, t_exec *exec_node)
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
	
	// ADICIONANDO OS BUILTINS QUE ESTAVAM FALTANDO:
	if (ft_strcmp(cmd, "pwd") == 0)
	{
		ft_pwd();
		return (0);
	}
	if (ft_strcmp(cmd, "echo") == 0)
	{
		return (ft_echo(exec_node));
	}
	if (ft_strcmp(cmd, "env") == 0)
	{
		print_env_lst(shell->envp);
		return (0);
	}
	
	// Se chegou até aqui, comando não reconhecido
	return (1);
}

/**
 * execute_regular_builtin - Executa builtins que podem rodar em processo filho
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com informações do comando
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
 * process_builtins - Processa comando builtin, decidindo onde executar
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com informações do comando
 *
 * Decide se o builtin deve rodar no processo pai ou filho e executa.
 *
 * Return: código de saída do comando
 */
int	process_builtins(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (1);
	
	// SIMPLIFICADO: todos os builtins rodam no processo pai
	return (exec_parent_builtin(shell, exec_node));
}