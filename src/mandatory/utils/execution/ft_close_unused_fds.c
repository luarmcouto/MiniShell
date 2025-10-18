/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_unused_fds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:14:06 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 11:30:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_unused_fds(t_cmd *current_cmd, t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd != current_cmd)
		{
			if (cmd->infd != STDIN_FILENO && cmd->infd != current_cmd->infd
				&& cmd->infd != current_cmd->outfd)
				close(cmd->infd);
			if (cmd->outfd != STDOUT_FILENO && cmd->outfd != current_cmd->infd
				&& cmd->outfd != current_cmd->outfd)
				close(cmd->outfd);
		}
		cmd = cmd->next;
	}
}
