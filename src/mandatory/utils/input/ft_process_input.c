/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/26 18:41:24 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_handle_syntax(char **argv, t_data *data)
{
	if (ft_check_syntax_errors(argv, data->argc))
	{
		data->last_exit_status = 2;
		ft_free_char_array(argv);
		if (!data->isatty)
			exit(2);
		return (1);
	}
	return (0);
}

static int	ft_check_quotes_and_split(char *input, t_data *data, char ***argv)
{
	if (ft_check_unclosed_quotes(input))
	{
		ft_handle_error(15, 2, NULL, NULL);
		data->last_exit_status = 2;
		free(input);
		return (0);
	}
	data->argc = ft_count_args(input);
	*argv = ft_split_input(input, data->argc);
	free(input);
	return (1);
}

static void	ft_count_cmds(t_data *data, t_cmd *cmd_list)
{
	t_cmd	*tmp;

	data->cmd_count = 0;
	tmp = cmd_list;
	while (tmp && ++data->cmd_count)
		tmp = tmp->next;
}

int	ft_process_input(char *input, t_data *data, t_cmd **cmd_list, int debug)
{
	char	**argv;
	char	**expanded_argv;

	if (!ft_check_quotes_and_split(input, data, &argv))
		return (0);
	if (ft_handle_syntax(argv, data))
		return (0);
	expanded_argv = ft_handle_env_expansion(argv, data);
	*cmd_list = ft_parse_input(expanded_argv, data);
	if (!*cmd_list)
	{
		ft_free_char_array(argv);
		if (expanded_argv != argv)
			ft_free_char_array(expanded_argv);
		return (0);
	}
	if (debug)
		ft_show_debug(argv, data->argc, expanded_argv, *cmd_list);
	ft_free_char_array(argv);
	if (expanded_argv != argv)
		ft_free_char_array(expanded_argv);
	ft_count_cmds(data, *cmd_list);
	return (1);
}
