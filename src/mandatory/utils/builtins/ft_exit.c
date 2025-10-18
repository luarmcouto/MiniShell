/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:11:55 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/08 10:06:29 by iwietzke         ###   ########.fr       */
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
	if (result > (limit - (digit - '0')) / 10)
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

int	ft_exit(t_cmd *cmd)
{
	char		**args;
	int			arg_count;
	long long	value;

	args = cmd->argv;
	if (!args)
		exit(0);
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count == 1)
		exit(0);
	if (arg_count > 2)
		exit(ft_handle_error(7, EXIT_FAILURE, NULL, NULL));
	if (!ft_is_numeric(args[1]))
		exit(ft_handle_error(14, 255, NULL, NULL));
	value = ft_atoll(args[1]);
	exit((int)(value % 256));
}
