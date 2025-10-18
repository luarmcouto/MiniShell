/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:15:13 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:55:17 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>
#include <unistd.h>

static int	ft_is_builtin(t_cmd *current)
{
	char	*cmd;

	if (!current || !current->argv || !current->argv[0])
		return (0);
	cmd = current->argv[0];
	if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0
		|| strcmp(cmd, "pwd") == 0 || strcmp(cmd, "export") == 0
		|| strcmp(cmd, "unset") == 0 || strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	ft_exec_child_process(t_cmd *current, t_cmd *cmd_list)
{
	int	exit_status;

	ft_setup_child_io(current, cmd_list);
	exit_status = ft_exec_cmd(current);
	exit(exit_status);
}

static int	ft_handle_fork(t_cmd *current, t_cmd *cmd_list, pid_t *pids)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec_child_process(current, cmd_list);
	else if (pid > 0)
	{
		pids[current->index] = pid;
		return (0);
	}
	else
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

static int	ft_execute_command(t_cmd *current, t_cmd *cmd_list, pid_t *pids,
		t_data **data)
{
	if (current->has_error == 1)
	{
		if (current->outfd != STDOUT_FILENO)
			close(current->outfd);
		ft_execute_error_command(current, cmd_list, pids);
		return (0);
	}
	if (ft_is_builtin(current))
	{
		(*data)->last_exit_status = ft_handle_builtins(current, data,
				cmd_list, pids);
		return (1);
	}
	return (ft_handle_fork(current, cmd_list, pids));
}

int	ft_execute_pipeline(t_cmd *cmd_list, pid_t *pids, t_data **data)
{
	t_cmd	*current;
	int		result;

	current = cmd_list;
	while (current)
	{
		result = ft_execute_command(current, cmd_list, pids, data);
		if (result == -1)
			return (-1);
		current = current->next;
	}
	current = cmd_list;
	while (current)
	{
		if (current->infd != STDIN_FILENO)
			close(current->infd);
		if (current->outfd != STDOUT_FILENO)
			close(current->outfd);
		current = current->next;
	}
	return (0);
}
