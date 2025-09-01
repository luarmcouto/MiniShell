/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cd(t_shell *shell_data, t_exec *cmd_node)
{
	char	*target_path;
	int		arg_count;

	arg_count = 0;
	while (cmd_node->argv[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (display_cd_error(NULL, "too many arguments"));
	target_path = determine_cd_path(shell_data, cmd_node->argv[1]);
	if (!target_path)
	{
		return (1);
	}
	if (chdir(target_path) != 0)
	{
		return (handle_chdir_failure(target_path));
	}
	return (refresh_pwd_variables(shell_data));
}

char	*determine_cd_path(t_shell *shell_data, char *provided_arg)
{
	char	*home_dir;
	char	*prev_dir;

	if (!provided_arg)
	{
		home_dir = get_shell_env(shell_data->envp, "HOME");
		if (!home_dir)
			return (display_cd_error(NULL, "HOME not set"), NULL);
		return (home_dir);
	}
	if (ft_strcmp(provided_arg, "-") == 0)
	{
		prev_dir = get_shell_env(shell_data->envp, "OLDPWD");
		if (!prev_dir)
			return (display_cd_error(NULL, "OLDPWD not set"), NULL);
		ft_putendl_fd(prev_dir, 1);
		return (prev_dir);
	}
	return (provided_arg);
}

int	refresh_pwd_variables(t_shell *shell_data)
{
	char	*previous_pwd;
	char	*current_path;

	current_path = get_shell_env(shell_data->envp, "PWD");
	if (current_path)
		previous_pwd = ft_strdup(current_path);
	else
		previous_pwd = ft_strdup("");
	if (!previous_pwd)
		exit_failure(shell_data, "cd: oldpwd allocation");
	return (update_new_pwd(shell_data, previous_pwd));
}

int	update_new_pwd(t_shell *shell_data, char *old_dir)
{
	char	*new_pwd;
	char	*pwd_variable;
	char	*oldpwd_variable;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(old_dir), display_cd_error(NULL,
				"error retrieving current directory"));
	pwd_variable = ft_strjoin("PWD=", new_pwd);
	oldpwd_variable = ft_strjoin("OLDPWD=", old_dir);
	if (!pwd_variable || !oldpwd_variable)
		exit_failure(shell_data, "cd: var allocation");
	export_variable(shell_data, pwd_variable);
	export_variable(shell_data, oldpwd_variable);
	free(new_pwd);
	free(pwd_variable);
	free(old_dir);
	free(oldpwd_variable);
	return (0);
}