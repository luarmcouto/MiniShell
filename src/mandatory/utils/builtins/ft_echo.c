/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 11:29:29 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_putarg_echo(char *arg, int flag_n, int outfd)
{
	int	i;
	
	(void)flag_n;
	if (!arg)
		return (0);
	
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1] == 'n')
		{
			if (ft_putchar_fd('\\', outfd) == -1)
				return (-1);
			if (ft_putchar_fd('n', outfd) == -1)
				return (-1);
			i += 2;
			continue;
		}
		if (ft_putchar_fd(arg[i], outfd) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	ft_is_flag_n(char *arg)
{
	if (arg && arg[0] == '-' && arg[1] == 'n')
		return (1);
	return (0);
}

static int	ft_print_args(char **argv, int start, int outfd)
{
	int	i;

	i = start;
	while (argv[i])
	{
		if (ft_putarg_echo(argv[i], 0, outfd) == -1)
			return (1);
		if (argv[i + 1])
		{
			if (ft_putchar_fd(' ', outfd) == -1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(t_cmd cmd)
{
	int	n_flag;
	int	start_index;

	if (!cmd.argv || !cmd.argv[0] || cmd.outfd < 0)
		return (1);
	n_flag = 0;
	start_index = 1;
	if (cmd.argv[1] && ft_is_flag_n(cmd.argv[1]))
	{
		n_flag = 1;
		start_index = 2;
	}
	if (ft_print_args(cmd.argv, start_index, cmd.outfd) != 0)
		return (1);
	if (!n_flag)
	{
		if (ft_putchar_fd('\n', cmd.outfd) == -1)
			return (1);
	}
	return (0);
}
