/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/08 09:53:18 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_valid_identifier(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_exported_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_print_var(envp[i]);
		i++;
	}
}

static int	ft_export_with_value(const char *arg, char *equals_pos,
		char ***envp)
{
	char	*name;
	char	*value;
	int		result;

	name = ft_substr((char *)arg, 0, equals_pos - arg);
	value = ft_strdup(equals_pos + 1);
	result = ft_setenv(name, value, envp);
	free(name);
	free(value);
	return (result != 0);
}

static int	ft_export_variable(const char *arg, char ***envp)
{
	char	*equals_pos;
	int		result;

	if (!ft_is_valid_identifier(arg))
		return (ft_handle_error(13, 1, NULL, NULL));
	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
		return (ft_export_with_value(arg, equals_pos, envp));
	result = ft_setenv((char *)arg, NULL, envp);
	return (result != 0);
}

int	ft_export(char **argv, char ***envp)
{
	int	i;
	int	exit_status;

	if (!argv[1])
	{
		ft_print_exported_vars(*envp);
		return (0);
	}
	exit_status = 0;
	i = 1;
	while (argv[i])
	{
		if (ft_export_variable(argv[i], envp) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
