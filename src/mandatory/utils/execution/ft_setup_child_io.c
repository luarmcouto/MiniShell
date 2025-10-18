/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_child_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:16:07 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 19:51:58 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <signal.h>
#include <unistd.h>

static void	ft_setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

static void	ft_redirect_io(t_cmd *current)
{
	if (current->infd != STDIN_FILENO)
		dup2(current->infd, STDIN_FILENO);
	if (current->outfd != STDOUT_FILENO)
		dup2(current->outfd, STDOUT_FILENO);
}

static void	ft_close_other_fds(t_cmd *temp, t_cmd *current)
{
	if (temp->infd != STDIN_FILENO && temp->infd != current->infd
		&& temp->infd != current->outfd)
		close(temp->infd);
	if (temp->outfd != STDOUT_FILENO && temp->outfd != current->infd
		&& temp->outfd != current->outfd)
		close(temp->outfd);
}

static void	ft_close_current_fds(t_cmd *temp, t_cmd *current)
{
	if (temp->infd != STDIN_FILENO && temp->infd != current->infd)
		close(temp->infd);
	if (temp->outfd != STDOUT_FILENO && temp->outfd != current->outfd)
		close(temp->outfd);
}

void	ft_setup_child_io(t_cmd *current, t_cmd *cmd_list)
{
	t_cmd	*temp;

	ft_setup_signals();
	ft_redirect_io(current);
	temp = cmd_list;
	while (temp)
	{
		if (temp != current)
			ft_close_other_fds(temp, current);
		else
			ft_close_current_fds(temp, current);
		temp = temp->next;
	}
}
