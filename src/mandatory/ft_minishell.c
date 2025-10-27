/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:47:21 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/27 22:28:32 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

static t_data	*ft_setup_minishell(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->last_exit_status = 0;
	ft_cpyenv(&data->envp, envp);
	data->isatty = isatty(STDIN_FILENO);
	if (data->isatty)
		ft_msg_start();
	ft_init_signals();
	return (data);
}

static int	execute_single_command(t_cmd *cmd_list, t_data **data)
{
	pid_t	*pids;

	pids = ft_calloc((*data)->cmd_count, sizeof(pid_t));
	if (!pids)
	{
		ft_free_cmd_list(cmd_list);
		return (0);
	}
	if (ft_execute_pipeline(cmd_list, pids, data) == -1)
	{
		free(pids);
		ft_free_cmd_list(cmd_list);
		return (-1);
	}
	ft_finish_execution(pids, (*data)->cmd_count, cmd_list, *data);
	return (1);
}

static int	process_command_loop(t_data *data, int debug)
{
	char	*input;
	t_cmd	*cmd_list;
	int		result;

	cmd_list = NULL;
	while (ft_read_input(&input, data))
	{
		if (!ft_process_input(input, data, &cmd_list, debug))
			continue ;
		result = execute_single_command(cmd_list, &data);
		if (result == -1)
			break ;
		cmd_list = NULL;
	}
	if (cmd_list)
		ft_free_cmd_list(cmd_list);
	return (0);
}

int	ft_minishell(char **envp, int debug)
{
	t_data	*data;
	int		exit_status;

	data = ft_setup_minishell(envp);
	if (!data)
		return (1);
	process_command_loop(data, debug);
	exit_status = data->last_exit_status;
	ft_free_char_array(data->envp);
	free(data);
	rl_clear_history();
	return (exit_status);
}
