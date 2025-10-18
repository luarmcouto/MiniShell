/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:48:17 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_create_env_string(char *name, char *value)
{
	char	*temp;
	char	*result;

	if (!value)
		return (ft_strdup(name));
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

void	ft_free_new_envp(char **new_envp)
{
	int	i;

	i = 0;
	while (new_envp[i])
		free(new_envp[i++]);
	free(new_envp);
}

int	ft_update_existing_env(char ***envp, char *name, char *value, int len)
{
	int		i;
	char	*new_var;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0
			&& ((*envp)[i][len] == '=' || (*envp)[i][len] == '\0'))
		{
			new_var = ft_create_env_string(name, value);
			if (!new_var)
				return (-1);
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_add_new_env(char ***envp, char *name, char *value)
{
	char	**new_envp;
	char	*new_var;
	int		envp_size;
	int		i;

	envp_size = ft_count_envp(*envp);
	new_envp = ft_realloc_envp(*envp, envp_size + 1);
	if (!new_envp)
		return (-1);
	new_var = ft_create_env_string(name, value);
	if (!new_var)
	{
		ft_free_new_envp(new_envp);
		return (-1);
	}
	new_envp[envp_size] = new_var;
	new_envp[envp_size + 1] = NULL;
	i = 0;
	while ((*envp)[i])
		free((*envp)[i++]);
	free(*envp);
	*envp = new_envp;
	return (0);
}
