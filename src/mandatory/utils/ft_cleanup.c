/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/25 18:46:03 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_exit_free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->argv)
			ft_free_char_array(cmd_list->argv);
		if (cmd_list->infd != STDIN_FILENO)
			close(cmd_list->infd);
		if (cmd_list->outfd != STDOUT_FILENO)
			close(cmd_list->outfd);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->envp)
		ft_free_char_array(data->envp);
	free(data);
}

void	ft_cleanup_and_exit(t_cmd *cmd_list, pid_t *pids, t_data *data,
		int exit_code)
{
	if (pids)
		free(pids);
	if (cmd_list)
		ft_exit_free_cmd_list(cmd_list);
	if (data)
		ft_free_data(data);
	rl_clear_history();
	exit(exit_code);
}