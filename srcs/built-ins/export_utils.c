/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:36 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 18:11:05 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_export_flag(t_shell *shell_data, const char *variable_name)
{
	t_list		*current;
	t_env_var	*env_variable;
	t_env_var	*new_env;

	current = shell_data->envp;
	while (current)
	{
		env_variable = current->content;
		if (is_exact_variable(env_variable, variable_name))
		{
			env_variable->is_export = true;
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env_var));
	if (!new_env)
		exit_failure(shell_data, "set_export_flag");
	new_env->value = ft_strdup(variable_name);
	new_env->content = NULL;
	new_env->is_export = true;
	new_env->printed = false;
	ft_lstadd_back(&shell_data->envp, ft_lstnew(new_env));
}

void	display_export_list(t_list *env_lst)
{
	t_list		*current;
	t_env_var	*env_var;
	int			i;
	int			size;

	size = ft_lstsize(env_lst);
	i = 0;
	while (i < size)
	{
		current = find_next_variable(env_lst);
		if (!current)
			break ;
		env_var = current->content;
		env_var->printed = true;
		display_variable(env_var);
		i++;
	}
	clear_printed_flags(env_lst);
}

void	clear_printed_flags(t_list *env_lst)
{
	t_list		*current;
	t_env_var	*env_var;

	current = env_lst;
	while (current)
	{
		env_var = current->content;
		env_var->printed = false;
		current = current->next;
	}
}

t_list	*find_next_variable(t_list *env_lst)
{
	t_list		*current;
	t_list		*smallest;
	t_env_var	*current_env;
	t_env_var	*smallest_env;

	smallest = NULL;
	current = env_lst;
	while (current)
	{
		current_env = current->content;
		if (current_env->printed == false)
		{
			if (!smallest)
				smallest = current;
			else
			{
				smallest_env = smallest->content;
				if (ft_strcmp(current_env->value, smallest_env->value) < 0)
					smallest = current;
			}
		}
		current = current->next;
	}
	return (smallest);
}

void	display_variable(t_env_var *env_var)
{
	if (!env_var->content)
		printf("declare -x %s\n", env_var->value);
	else
	{
		printf("declare -x %s", env_var->value);
		printf("\"%s\"\n", env_var->content);
	}
}