/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:36 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 19:05:37 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	export_variable(t_shell *shell_data, const char *arg_str)
// {
// 	char	*equal_pos;
// 	char	*plus_pos;

// 	if (arg_str[0] == '_' && arg_str[1] == '=')
// 		return (0);
// 	if (!is_valid_var_identifier(arg_str))
// 	{
// 		display_invalid_identifier((char *)arg_str, "export");
// 		return (1);
// 	}
// 	equal_pos = ft_strchr(arg_str, '=');
// 	plus_pos = ft_strchr(arg_str, '+');
// 	return (handle_export_variable(shell_data, arg_str, equal_pos, plus_pos));
// }

char	*build_value(t_shell *shell_data, const char *arg_str, char *equal_pos)
{
	char	*value;
	int		value_len;

	if (!equal_pos)
		return (ft_strdup(arg_str));
	value_len = equal_pos - arg_str + 1;
	value = malloc(sizeof(char) * (value_len + 1));
	if (!value)
		exit_failure(shell_data, "build_value");
	ft_strlcpy(value, arg_str, value_len + 1);
	return (value);
}

void	modify_existing_var(t_env_var *env_variable, t_env_var *new_variable)
{
	char	*temp_content;
	char	*plus_sign;

	plus_sign = ft_strnstr(new_variable->value, "+=", ft_strlen(new_variable->value));
	if (plus_sign)
	{
		temp_content = ft_strjoin(env_variable->content, new_variable->content);
		free(env_variable->content);
		env_variable->content = temp_content;
		free(new_variable->value);
		free(new_variable->content);
	}
	else
	{
		free(env_variable->value);
		free(env_variable->content);
		env_variable->value = new_variable->value;
		env_variable->content = new_variable->content;
	}
	env_variable->is_export = true;
	env_variable->printed = false;
	free(new_variable);
}

void	handle_append_operation(t_shell *shell_data, t_env_var *new_variable, 
			const char *arg_str, char *plus_pos)
{
	char	*var_name;
	char	*value;
	int		name_len;

	name_len = plus_pos - arg_str;
	var_name = ft_substr(arg_str, 0, name_len);
	if (!var_name)
		exit_failure(shell_data, "handle_append_operation");
	new_variable->content = ft_strdup(plus_pos + 2);
	value = ft_strjoin(var_name, "=");
	new_variable->value = value;
	if (!new_variable->content || !new_variable->value)
		exit_failure(shell_data, "handle_append_operation");
	free(var_name);
}