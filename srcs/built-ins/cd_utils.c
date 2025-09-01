/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_chdir_failure(char *directory)
{
	if (errno == ENOENT)
		return (display_cd_error(directory, "No such file or directory"));
	if (errno == ENOTDIR)
		return (display_cd_error(directory, "Not a directory"));
	if (errno == EACCES)
		return (display_cd_error(directory, "Permission denied"));
	return (display_cd_error(directory, "chdir failed"));
}

int	display_cd_error(char *dir_path, char *error_msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (dir_path)
	{
		ft_putstr_fd(dir_path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error_msg, 2);
	return (1);
}