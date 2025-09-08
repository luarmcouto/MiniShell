/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:40 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 19:06:09 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_var_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	display_invalid_identifier(char *arg_str, char *cmd_str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg_str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	remove_environment_var(t_shell *shell_data, const char *variable_name)
{
	t_list	*previous;

	if (check_first_env_node(shell_data, variable_name))
		return ;
	previous = find_previous_node(shell_data->envp, variable_name);
	if (previous)
		remove_env_node(previous);
}

int	is_exact_variable(t_env_var *env_variable, const char *variable_name)
{
	char	*plus_sign;
	char	*equals_var;
	char	*equals_env;
	size_t	len_name;
	size_t	len_env;

	plus_sign = ft_strnstr(variable_name, "+=", ft_strlen(variable_name));
	equals_var = ft_strchr(variable_name, '=');
	equals_env = ft_strchr(env_variable->value, '=');
	
	if (plus_sign)
		len_name = plus_sign - variable_name;
	else if (equals_var)
		len_name = equals_var - variable_name;
	else
		len_name = ft_strlen(variable_name);
	
	if (equals_env)
		len_env = equals_env - env_variable->value;
	else
		len_env = ft_strlen(env_variable->value);
	
	if (len_name != len_env)
		return (0);
	return (ft_strncmp(env_variable->value, variable_name, len_name) == 0);
}
