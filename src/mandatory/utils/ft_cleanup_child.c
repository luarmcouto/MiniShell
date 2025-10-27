/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/26 18:15:47 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_cleanup(t_cmd *cmd, char *path)
{
	if (path)
		free(path);
	if (cmd)
	{
		if (cmd->argv)
			ft_free_char_array(cmd->argv);
		if (cmd->infd != STDIN_FILENO)
			close(cmd->infd);
		if (cmd->outfd != STDOUT_FILENO)
			close(cmd->outfd);
		if (cmd->data)
		{
			if (cmd->data->envp)
				ft_free_char_array(cmd->data->envp);
			free(cmd->data);
		}
		free(cmd);
	}
}
