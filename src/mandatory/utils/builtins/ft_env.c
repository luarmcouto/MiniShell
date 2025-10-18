/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/08 09:53:43 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_cmd cmd, char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			dprintf(cmd.outfd, "%s\n", envp[i]);
		i++;
	}
	return (0);
}

void	ft_print_var(char *env_str)
{
	int		j;
	char	*name;
	char	*value;

	j = 0;
	while (env_str[j] && env_str[j] != '=')
		j++;
	name = ft_substr(env_str, 0, j);
	if (env_str[j] == '=')
	{
		value = ft_substr(env_str, j + 1, ft_strlen(env_str) - j - 1);
		ft_fprintf(1, "declare -x %s=\"%s\"\n", name, value);
		free(value);
	}
	else
		ft_fprintf(1, "declare -x %s\n", name);
	free(name);
}
