/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:25:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/02 17:52:10 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_redir(const char *s)
{
	return (ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0
		|| ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

static int	is_logical_op(const char *s)
{
	return (ft_strcmp(s, "||") == 0 || ft_strcmp(s, "&&") == 0);
}

static int	is_pipe_like(const char *s)
{
	return (ft_strcmp(s, "|") == 0 || is_logical_op(s)
		|| ft_strcmp(s, "&") == 0);
}

static int	ft_check_token_errors(char **argv, int argc, int i)
{
	if (is_pipe_like(argv[i]))
	{
		if (i == argc - 1)
			return (ft_handle_error(5, 2, NULL, NULL));
		if (is_pipe_like(argv[i + 1]))
			return (ft_handle_error(6, 2, argv[i + 1], NULL));
	}
	if (is_redir(argv[i]))
	{
		if (i == argc - 1)
			return (ft_handle_error(5, 2, NULL, NULL));
		if (is_pipe_like(argv[i + 1]) || is_redir(argv[i + 1]))
			return (ft_handle_error(6, 2, argv[i + 1], NULL));
	}
	return (0);
}

int	ft_check_syntax_errors(char **argv, int argc)
{
	int	i;
	int	error;

	if (!argv || argc == 0)
		return (0);
	if (ft_strcmp(argv[0], "|") == 0 || is_logical_op(argv[0])
		|| ft_strcmp(argv[0], "&") == 0)
		return (ft_handle_error(6, 2, argv[0], NULL));
	if (is_redir(argv[0]) && argc == 1)
		return (ft_handle_error(5, 2, NULL, NULL));
	i = 0;
	while (i < argc)
	{
		error = ft_check_token_errors(argv, argc, i);
		if (error)
			return (error);
		i++;
	}
	return (0);
}
