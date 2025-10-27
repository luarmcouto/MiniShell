/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:11:55 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/27 21:16:30 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <limits.h>

static int	ft_check_overflow(long long result, char digit, int sign)
{
	unsigned long long	limit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	if ((unsigned long long)result > (limit - (digit - '0')) / 10)
		return (1);
	return (0);
}

static int	ft_parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_is_numeric(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	sign = ft_parse_sign(str, &i);
	if (str[i] == '\0')
		return (0);
	result = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (ft_check_overflow(result, str[i], sign))
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_exit(t_cmd *cmd, t_cmd *cmd_list, pid_t *pids, t_data *data)
{
	char		**args;
	int			arg_count;
	int			exit_code;

	args = cmd->argv;
	if (!args)
		ft_cleanup_and_exit(cmd_list, pids, data, 0);
	arg_count = ft_countargs(args);
	if (arg_count == 1)
		ft_cleanup_and_exit(cmd_list, pids, data, 0);
	if (arg_count > 2)
	{
		ft_handle_error(7, EXIT_FAILURE, NULL, NULL);
		ft_cleanup_and_exit(cmd_list, pids, data, EXIT_FAILURE);
	}
	if (!ft_is_numeric(args[1]))
	{
		ft_handle_error(14, 255, NULL, NULL);
		ft_cleanup_and_exit(cmd_list, pids, data, 255);
	}
	exit_code = (int)(ft_atoll(args[1]) % 256);
	ft_cleanup_and_exit(cmd_list, pids, data, exit_code);
	return (0);
}
