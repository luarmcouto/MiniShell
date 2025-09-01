/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:33 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 16:48:52 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_shell	*shell_struct(t_shell *shell, int flag)
{
	static t_shell	*ptr;

	if (flag)
		return (ptr);
	ptr = shell;
	return (ptr);
}

void	sigint_heredoc_handler(int sig)
{
	const t_shell	*shell = shell_struct(NULL, 1);

	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(shell->fd);
		free_env_list(shell->envp);
		free_shell((t_shell *)shell);
		exit_code(130);
		exit(130);
	}
}

void	heredoc_signal(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}