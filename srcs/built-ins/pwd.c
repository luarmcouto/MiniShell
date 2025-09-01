/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(void)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		printf("%s\n", current_dir);
	}
	else
	{
		perror("pwd error:");
	}
}
