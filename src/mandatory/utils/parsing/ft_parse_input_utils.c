/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:17:21 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/17 20:17:28 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_fd_to_cmd(t_cmd *cmd, int fd, int in_or_out)
{
	if (!cmd)
		return ;
	if (in_or_out == 0)
	{
		if (cmd->infd != STDIN_FILENO)
			close(cmd->infd);
		cmd->infd = fd;
	}
	else
	{
		if (cmd->outfd != STDOUT_FILENO)
			close(cmd->outfd);
		cmd->outfd = fd;
	}
}

t_cmd	*ft_create_cmd_node(int index)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->infd = STDIN_FILENO;
	new_cmd->outfd = STDOUT_FILENO;
	new_cmd->has_error = 0;
	new_cmd->index = index;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_argv;

	if (!cmd || !cmd->argv)
	{
		if (cmd)
			ft_init_cmd_argv(cmd, arg);
		return ;
	}
	i = 0;
	while (cmd->argv[i])
		i++;
	new_argv = malloc((i + 2) * sizeof(char *));
	if (!new_argv)
		return ;
	i = -1;
	while (cmd->argv[++i])
		new_argv[i] = cmd->argv[i];
	new_argv[i] = arg;
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

t_cmd	*ft_handle_pipe(t_cmd *current_cmd, int *cmd_index, t_data *data)
{
	int		pipefd[2];
	t_cmd	*new_cmd;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), current_cmd);
	(*cmd_index)++;
	new_cmd = ft_create_cmd_node(*cmd_index);
	if (!new_cmd)
		return (current_cmd);
	new_cmd->data = data;
	current_cmd->next = new_cmd;
	if (current_cmd->outfd == STDOUT_FILENO)
		current_cmd->outfd = pipefd[1];
	else
		close(pipefd[1]);
	new_cmd->infd = pipefd[0];
	return (new_cmd);
}

int	ft_handle_redir(char **argv, int i, t_cmd *cmd, t_data *data)
{
	char	*clean_arg;
	int		fd;

	clean_arg = ft_remove_quotes(argv[i + 1]);
	if (!clean_arg)
		clean_arg = argv[i + 1];
	if (ft_strcmp(argv[i], "<") == 0)
		fd = ft_handle_infile(clean_arg);
	else if (ft_strcmp(argv[i], ">") == 0)
		fd = ft_handle_outfile(clean_arg, 0);
	else if (ft_strcmp(argv[i], ">>") == 0)
		fd = ft_handle_outfile(clean_arg, 1);
	else
		fd = ft_handle_heredoc(clean_arg);
	if (fd != -1)
		ft_add_fd_to_cmd(cmd, fd, !(ft_strcmp(argv[i], "<") == 0
				|| ft_strcmp(argv[i], "<<") == 0));
	else
	{
		data->last_exit_status = 1;
		cmd->has_error = 1;
	}
	if (clean_arg != argv[i + 1])
		free(clean_arg);
	return (1);
}
