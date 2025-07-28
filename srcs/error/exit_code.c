/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:37:44 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 19:20:35 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*itoa_exit(t_shell *shell, char **str)
{
	char	*code;
	char	*tmp;

	code = ft_itoa(exit_code(-1));
	if (!code)
		exit_failure(shell, "itoa_exit");
	tmp = *str;
	*str = ft_strjoin(*str, code);
	free(tmp);
	free(code);
	if (!*str)
		exit_failure(shell, "itoa_exit_2");
	return (*str);
}

int	exit_code(int value)
{
	static int	code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}

int	last_process(int value)
{
	static int	code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}

void	exit_status(int status)
{
	if (WIFEXITED(status))
		exit_code(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit_code(128 + WTERMSIG(status));
}

void	exit_failure(t_shell *shell, char *function)
{
	free_env_lst(shell->envp);
	free_shell(shell);
	ft_putstr_fd(RED"malloc error: "DEFAULT, 2);
	ft_putendl_fd(function, 2);
	exit(1);
}