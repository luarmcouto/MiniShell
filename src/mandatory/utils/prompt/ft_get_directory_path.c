/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_directory_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:44:08 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/02 17:55:00 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_create_tilde_path(char *pwd, int home_len, int pwd_len)
{
	char	*result;

	if (pwd_len == home_len)
		return (ft_strdup("~"));
	if (pwd[home_len] == '/')
	{
		result = malloc(pwd_len - home_len + 2);
		if (!result)
			return (ft_strdup(pwd));
		result[0] = '~';
		ft_strcpy(result + 1, pwd + home_len);
		return (result);
	}
	return (NULL);
}

static char	*ft_replace_home_with_tilde(char *pwd, char *home)
{
	int		home_len;
	int		pwd_len;
	char	*result;

	home_len = ft_strlen(home);
	pwd_len = ft_strlen(pwd);
	if (pwd_len >= home_len && ft_strncmp(pwd, home, home_len) == 0)
	{
		result = ft_create_tilde_path(pwd, home_len, pwd_len);
		if (result)
			return (result);
	}
	return (ft_strdup(pwd));
}

char	*ft_get_directory_path(char **envp)
{
	char	*pwd;
	char	*home;

	pwd = ft_getenv("PWD", envp);
	if (!pwd || !*pwd)
		return (ft_strdup("(unknown)"));
	home = ft_getenv("HOME", envp);
	if (!home)
		return (ft_strdup(pwd));
	return (ft_replace_home_with_tilde(pwd, home));
}
