/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:17:21 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/02 16:57:17 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_redirect(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (1);
	if (ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

static void	ft_process_pipe(t_cmd **current, int *cmd_idx, t_data *data)
{
	*current = ft_handle_pipe(*current, cmd_idx, data);
}

static void	ft_process_redir(char **argv, int *i, t_cmd *cmd, t_data *data)
{
	if (cmd->has_error == 0)
		ft_handle_redir(argv, *i, cmd, data);
	(*i)++;
}

static void	ft_process_arg(char **argv, int i, t_cmd *cmd)
{
	char	*arg;
	char	*clean_arg;

	arg = argv[i];
	clean_arg = ft_remove_quotes(arg);
	if (clean_arg)
		ft_add_arg_to_cmd(cmd, clean_arg);
}

t_cmd	*ft_parse_input(char **argv, t_data *data)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	int		i;
	int		cmd_index;

	if (!argv || data->argc == 0)
		return (NULL);
	cmd_index = 0;
	cmd_list = ft_create_cmd_node(cmd_index);
	if (!cmd_list)
		return (NULL);
	current_cmd = cmd_list;
	current_cmd->data = data;
	i = -1;
	while (++i < data->argc)
	{
		if (ft_strcmp(argv[i], "|") == 0)
			ft_process_pipe(&current_cmd, &cmd_index, data);
		else if (ft_is_redirect(argv[i]))
			ft_process_redir(argv, &i, current_cmd, data);
		else
			ft_process_arg(argv, i, current_cmd);
	}
	return (cmd_list);
}
