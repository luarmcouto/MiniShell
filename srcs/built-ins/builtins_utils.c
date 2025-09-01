/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/01 18:05:43 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Função placeholder para export (será implementada no domingo)
void	builtin_export(t_shell *shell_data, char **arguments)
{
	(void)shell_data;
	(void)arguments;
	// TODO: Implementar export no domingo
	printf("minishell: export: not implemented yet\n");
}

int	is_builtin_command(const char *cmd)
{
	const char	*builtin_list[7] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp((char *)cmd, (char *)builtin_list[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_shell_builtin(t_exec *cmd_node)
{
	char	*command;

	command = NULL;
	if (cmd_node->argv)
		command = cmd_node->argv[0];
	if (!command)
		return (0);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	return (0);
}

int	execute_shell_builtin(t_shell *shell_data, t_exec *cmd_node)
{
	char	*command;

	command = cmd_node->argv[0];
	if (!command)
		return (1);
	if (!ft_strcmp(command, "exit"))
	{
		ft_putstr_fd("exit\n", 2);
		return (builtin_exit(shell_data, cmd_node), 0);
	}
	if (!ft_strcmp(command, "export"))
	{
		builtin_export(shell_data, cmd_node->argv);
		return (exit_code(-1));
	}
	if (!ft_strcmp(command, "unset"))
		return ((builtin_unset(shell_data, cmd_node->argv)), 0);
	if (!ft_strcmp(command, "cd"))
		return ((builtin_cd(shell_data, cmd_node)));
	return (1);
}

int	execute_regular_builtin(t_shell *shell_data, t_exec *cmd_node)
{
	char	*command;

	command = cmd_node->argv[0];
	if (!command)
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (builtin_exit(shell_data, cmd_node), 0);
	if (!ft_strcmp(command, "echo"))
		return (builtin_echo(cmd_node));
	if (!ft_strcmp(command, "pwd"))
		return (builtin_pwd(), 0);
	if (!ft_strcmp(command, "env"))
		return (display_env_list(shell_data->envp), 0);
	if (!ft_strcmp(command, "export") && !cmd_node->argv[1])
		return (builtin_export(shell_data, cmd_node->argv), 0);
	return (1);
}

int	process_builtins(t_shell *shell_data, t_exec *cmd_node)
{
	if (!cmd_node || !cmd_node->argv[0])
		return (1);
	if (is_shell_builtin(cmd_node))
	{
		return (execute_shell_builtin(shell_data, cmd_node));
	}
	return (execute_regular_builtin(shell_data, cmd_node));
}