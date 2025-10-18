/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:33 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 19:16:53 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <errno.h>

static char	*ft_get_target_dir(char **argv, char **envp)
{
	char	*target_dir;

	if (!argv[1])
	{
		target_dir = ft_getenv("HOME", envp);
		if (!target_dir)
			return (NULL);
		return (target_dir);
	}
	if (ft_strcmp(argv[1], "~") == 0)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
			return (NULL);
		return (target_dir);
	}
	return (argv[1]);
}

static void	ft_update_pwd_vars(char *oldpwd, char ***envp)
{
	char	buf[4096];

	if (getcwd(buf, sizeof(buf)))
	{
		if (oldpwd)
			ft_setenv("OLDPWD", oldpwd, envp);
		ft_setenv("PWD", buf, envp);
	}
	else
	{
		if (oldpwd)
			ft_setenv("OLDPWD", oldpwd, envp);
	}
}

int	ft_cd(char **argv, char ***envp)
{
	char	*oldpwd;
	char	*target_dir;

	if (!argv || !envp)
		return (1);
	target_dir = ft_get_target_dir(argv, *envp);
	if (!target_dir)
		return (ft_handle_error(8, EXIT_FAILURE, NULL, NULL));
	if (chdir(target_dir) != 0)
		return (ft_handle_error(11, EXIT_FAILURE, target_dir, strerror(errno)));
	oldpwd = getenv("PWD");
	ft_update_pwd_vars(oldpwd, envp);
	return (0);
}
