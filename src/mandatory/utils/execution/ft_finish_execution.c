/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:10:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/20 13:56:14 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->argv)
			ft_free_char_array(cmd_list->argv);
		free(cmd_list);
		cmd_list = tmp;
	}
}

static int	ft_get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

static int	ft_wait_processes(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	last_exit_status;
	int	executed_processes;

	last_exit_status = 0;
	executed_processes = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			last_exit_status = ft_get_exit_status(status);
			executed_processes = 1;
		}
		i++;
	}
	if (!executed_processes)
		return (-1);
	return (last_exit_status);
}

void	ft_finish_execution(pid_t *pids, int cmd_count, t_cmd *cmd_list,
		t_data *data)
{
	int	exit_status;

	exit_status = ft_wait_processes(pids, cmd_count);
	if (exit_status != -1)
		data->last_exit_status = exit_status;
	free(pids);
	ft_free_cmd_list(cmd_list);
	//cmd_list = NULL;
}
