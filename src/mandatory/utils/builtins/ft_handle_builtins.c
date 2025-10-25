/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:43:33 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 11:28:28 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

static int	ft_exec_builtin(t_cmd *cmd, t_data **data, t_cmd *cmd_list, pid_t *pids)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(*cmd));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->argv, &(*data)->envp));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(*cmd));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->argv, &(*data)->envp));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->argv, &(*data)->envp));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(*cmd, (*data)->envp));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd, cmd_list, pids, *data);
	return (-1);
}

static int	ft_exec_builtin_child(t_cmd *cmd, t_data **data, t_cmd *cmd_list, pid_t *pids)
{
	int	status;

	ft_setup_child_io(cmd, cmd_list);
	status = ft_exec_builtin(cmd, data, cmd_list, pids);
	exit(status);
}

static int	ft_handle_builtin_fork(t_cmd *cmd, t_data **data, t_cmd *cmd_list,
		pid_t *pids)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec_builtin_child(cmd, data, cmd_list, pids);
	else if (pid > 0)
	{
		if (pids)
			pids[cmd->index] = pid;
		return (0);
	}
	else
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

int	ft_handle_builtins(t_cmd *cmd, t_data **data, t_cmd *cmd_list, pid_t *pids)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (-1);
	if (cmd->infd != STDIN_FILENO || cmd->outfd != STDOUT_FILENO)
		return (ft_handle_builtin_fork(cmd, data, cmd_list, pids));
	return (ft_exec_builtin(cmd, data, cmd_list, pids));
}
