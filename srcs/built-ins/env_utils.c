/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_shell_env(t_list *envp, const char *var_name)
{
	t_list		*current;
	t_env_var	*env_variable;
	char		*variable_with_eq;
	char		*result;

	variable_with_eq = ft_strjoin(var_name, "=");
	if (!variable_with_eq)
		return (NULL);
	current = envp;
	while (current)
	{
		env_variable = (t_env_var *)current->content;
		if (ft_strcmp(env_variable->value, variable_with_eq) == 0)
		{
			result = env_variable->content;
			free(variable_with_eq);
			return (result);
		}
		current = current->next;
	}
	free(variable_with_eq);
	return (NULL);
}

void	display_env_list(t_list *env_lst)
{
	t_list		*current;
	t_env_var	*env_variable;

	current = env_lst;
	while (current)
	{
		env_variable = (t_env_var *)current->content;
		printf("%s%s\n", env_variable->value, env_variable->content);
		current = current->next;
	}
}

void	free_env_list(t_list *envp)
{
	t_list		*current;
	t_list		*temp;
	t_env_var	*env_variable;

	current = envp;
	while (current)
	{
		temp = current->next;
		env_variable = (t_env_var *)current->content;
		free(env_variable->value);
		free(env_variable->content);
		free(env_variable);
		free(current);
		current = temp;
	}
}