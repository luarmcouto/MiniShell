/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:47:21 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/20 12:10:24 by luarodri         ###   ########.fr       */
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

int	ft_minishell(char **envp, int debug)
{
	char	*input;
	t_cmd	*cmd_list;
	t_data	*data;
	pid_t	*pids;
	int		exit_status;

	data = ft_setup_minishell(envp);
	if (!data)
		return (1);
	cmd_list = NULL;
	while (ft_read_input(&input, data))
	{
		if (!ft_process_input(input, data, &cmd_list, debug))
			continue ;
		pids = ft_calloc(data->cmd_count, sizeof(pid_t));
		if (!pids)
		{
			ft_free_cmd_list(cmd_list);
			continue ;
		}
		if (ft_execute_pipeline(cmd_list, pids, &data) == -1)
		{
			free(pids);
			ft_free_cmd_list(cmd_list);
			break ;
		}
		ft_finish_execution(pids, data->cmd_count, cmd_list, data);
		cmd_list = NULL;
	}
	if (cmd_list)
		ft_free_cmd_list(cmd_list);
	exit_status = data->last_exit_status;
	ft_free_char_array(data->envp);
	free(data);
	rl_clear_history();
	return (exit_status);
}
