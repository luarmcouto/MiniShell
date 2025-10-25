/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:06:20 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/20 13:59:14 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/stat.h>

static void	ft_compact_argv(char **argv)
{
	int	i;
	int	j;

	if (!argv)
		return;
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i] && ft_strlen(argv[i]) > 0)
		{
			if (i != j)
				argv[j] = argv[i];
			j++;
		}
		i++;
	}
	argv[j] = NULL;
}

static char	*ft_get_cmd_path(char *cmd_name, char **envp)
{
	char	*path;

	if (ft_strchr(cmd_name, '/'))
		path = ft_strdup(cmd_name);
	else
		path = get_cmd_path(cmd_name, envp);
	return (path);
}

static int	ft_validate_path(char *path, char *cmd_name)
{
	struct stat	file_stat;

	if (!path)
		return (ft_handle_error(1, EXIT_COMMAND_NOT_FOUND, cmd_name, NULL));
	if (stat(path, &file_stat) == -1)
	{
		free(path);
		return (ft_handle_error(4, EXIT_COMMAND_NOT_FOUND, cmd_name, NULL));
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		free(path);
		return (ft_handle_error(3, EXIT_PERMISSION_DENIED, cmd_name, NULL));
	}
	if (access(path, X_OK) == -1)
	{
		free(path);
		return (ft_handle_error(2, EXIT_PERMISSION_DENIED, cmd_name, NULL));
	}
	return (0);
}

int	ft_exec_cmd(t_cmd *cmd)
{
	char	*path;
	int		error;

	if (!cmd || !cmd->argv)
		return (!cmd);
	ft_compact_argv(cmd->argv);
	if (!cmd->argv[0])
		return (0);
	path = ft_get_cmd_path(cmd->argv[0],cmd->data->envp);
	error = ft_validate_path(path, cmd->argv[0]);
	if (error)
		return (error);
	if (!path || !cmd->argv || !cmd->data || !cmd->data->envp)
	{
		if (path)
			free(path);
		return (EXIT_FAILURE);
	}
	execve(path, cmd->argv, cmd->data->envp);
	perror("minishell: execve");
	free(path);
	return (EXIT_FAILURE);
}
