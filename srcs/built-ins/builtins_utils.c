/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/24 16:08:30 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(const char *command)
{
	const char	*builtins[7] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int			i;

	if (!command)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp((char *)command, (char *)builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_shell *shell, t_exec *exec_node)
{
	(void) shell;
	(void) exec_node;
	/*
	char	*cmd;

	if (!exec_node || !exec_node->argv || !exec_node->argv[0])
		return (1);
	
	cmd = exec_node->argv[0];
	if (!ft_strcmp(cmd, "echo"))
	return (ft_echo(exec_node));
	if (!ft_strcmp(cmd, "pwd"))
	return (ft_pwd(), 0);
	if (!ft_strcmp(cmd, "env"))
	return (print_env_lst(shell->envp), 0);
	if (!ft_strcmp(cmd, "cd"))
	return (ft_cd(shell, exec_node));
	if (!ft_strcmp(cmd, "export"))
	return (ft_export(shell, exec_node->argv), 0);
	if (!ft_strcmp(cmd, "unset"))
	return (ft_unset(shell, exec_node->argv), 0);
	if (!ft_strcmp(cmd, "exit"))
	return (ft_exit(shell, exec_node), 0);
	*/
	
	return (1);
}