/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/08 09:44:47 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_is_invalid_identifier(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0)
		return (1);
	if (arg[len - 1] == '=' || arg[len - 1] == '-')
		return (1);
	return (0);
}

static void	ft_shift_envp(char **envp, int start)
{
	int	k;

	k = start;
	while (envp[k])
	{
		envp[k] = envp[k + 1];
		k++;
	}
}

static int	ft_remove_var(char *var_name, char **envp)
{
	int	j;
	int	var_len;

	j = 0;
	var_len = ft_strlen(var_name);
	while (envp[j])
	{
		if (!ft_strncmp(envp[j], var_name, var_len)
			&& envp[j][var_len] == '=')
		{
			free(envp[j]);
			ft_shift_envp(envp, j);
			j--;
		}
		j++;
	}
	return (0);
}

int	ft_unset(char **args, char ***envp)
{
	int	i;

	if (!args || !envp || !*envp)
		return (1);
	i = 1;
	while (args[i])
	{
		if (ft_is_invalid_identifier(args[i]))
		{
			ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n",
				args[i]);
			return (1);
		}
		ft_remove_var(args[i], *envp);
		i++;
	}
	return (0);
}
