/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}

int	ft_echo(t_exec *cmd_node)
{
	bool	add_newline;
	int		arg_idx;

	add_newline = true;
	arg_idx = 1;
	while (cmd_node->argv[arg_idx] && check_no_newline_flag(cmd_node->argv[arg_idx]))
	{
		add_newline = false;
		arg_idx++;
	}
	print_echo_args(cmd_node->argv, arg_idx, add_newline);
	return (0);
}

int	check_no_newline_flag(char *argument)
{
	int	i;

	if (!argument || argument[0] != '-')
		return (0);
	i = 1;
	while (argument[i])
	{
		if (argument[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

void	print_echo_args(char **arguments, int start_idx, int add_newline)
{
	unsigned int	i;

	i = start_idx;
	while (arguments[i])
	{
		ft_putstr(arguments[i]);
		if (arguments[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (add_newline)
		write(1, "\n", 1);
}	