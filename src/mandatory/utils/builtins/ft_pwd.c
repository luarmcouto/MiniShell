/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 11:28:59 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_cmd cmd)
{
	char	cwd[1024];
	char	*output;
	int		len;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		len = ft_strlen(cwd);
		output = malloc(len + 2);
		if (!output)
			return (1);
		ft_strcpy(output, cwd);
		output[len] = '\n';
		output[len + 1] = '\0';
		write(cmd.outfd, output, len + 1);
		free(output);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
