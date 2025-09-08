/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:36 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 19:04:25 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env_var	*create_new_env_var(t_shell *shell_data, const char *var_name, 
			const char *var_value)
{
	t_env_var	*new_env;
	char		*equals_pos;

	new_env = malloc(sizeof(t_env_var));
	if (!new_env)
		exit_failure(shell_data, "create_new_env_var");
	equals_pos = ft_strchr(var_name, '=');
	if (equals_pos)
	{
		new_env->value = build_value(shell_data, var_name, equals_pos);
		new_env->content = ft_strdup(var_value);
	}
	else
	{
		new_env->value = ft_strdup(var_name);
		new_env->content = var_value ? ft_strdup(var_value) : NULL;
	}
	new_env->is_export = true;
	new_env->printed = false;
	return (new_env);
}

int	handle_export_variable(t_shell *shell_data, const char *arg_str, 
		char *equal_pos, char *plus_pos)
{
	t_env_var	*new_env;

	if (!equal_pos && !ft_strchr(arg_str, '='))
	{
		set_export_flag(shell_data, arg_str);
		return (0);
	}
	new_env = malloc(sizeof(t_env_var));
	if (!new_env)
		exit_failure(shell_data, "handle_export_variable");
	if (plus_pos && plus_pos[1] == '=')
		handle_append_operation(shell_data, new_env, arg_str, plus_pos);
	else
	{
		new_env->value = build_value(shell_data, arg_str, equal_pos);
		new_env->content = ft_strdup(equal_pos + 1);
	}
	new_env->is_export = true;
	new_env->printed = false;
	update_env_variable(shell_data, new_env->value, new_env->content);
	return (0);
}