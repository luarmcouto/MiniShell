/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:40 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 19:02:46 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * builtin_unset - Implementa o comando unset
 */
int	builtin_unset(t_shell *shell_data, char **arguments)
{
	int	i;
	int	exit_status;
	int	result;

	if (!arguments[1])
		return (0);

	exit_status = 0;
	i = 1;

	while (arguments[i])
	{
		result = unset_variable(shell_data, arguments[i]);
		if (result != 0)
			exit_status = 1;
		i++;
	}

	return (exit_status);
}

void	remove_first_env_node(t_shell *shell_data, t_list *current)
{
	t_env_var	*env_variable;

	env_variable = (t_env_var *)current->content;
	shell_data->envp = current->next;
	free(env_variable->value);
	free(env_variable->content);
	free(env_variable);
	free(current);
}

void	remove_env_node(t_list *previous)
{
	t_list		*current;
	t_env_var	*env_variable;

	if (!previous || !previous->next)
		return ;
	current = previous->next;
	env_variable = (t_env_var *)current->content;
	previous->next = current->next;
	free(env_variable->value);
	free(env_variable->content);
	free(env_variable);
	free(current);
}

int	check_first_env_node(t_shell *shell_data, const char *variable_name)
{
	t_list		*current;
	t_env_var	*env_variable;

	if (!shell_data->envp)
		return (0);
	current = shell_data->envp;
	env_variable = (t_env_var *)current->content;
	if (is_exact_variable(env_variable, variable_name))
	{
		remove_first_env_node(shell_data, current);
		return (1);
	}
	return (0);
}

t_list	*find_previous_node(t_list *env_lst, const char *variable_name)
{
	t_list		*current;
	t_env_var	*env_variable;

	if (!env_lst || !env_lst->next)
		return (NULL);
	current = env_lst;
	while (current->next)
	{
		env_variable = (t_env_var *)current->next->content;
		if (is_exact_variable(env_variable, variable_name))
			return (current);
		current = current->next;
	}
	return (NULL);
}