/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:45:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/21 21:51:14 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	syntax_error_msg(char *str)
{
	static bool	message_printed;

	message_printed = false;
	if (!message_printed)
	{
		ft_putstr_fd(SYNTAX_ERROR, 2);
		if (str)
			ft_putendl_fd(str, 2);
		message_printed = true;
	}
	else
		message_printed = false;
	return (true);
}

bool	ft_ismeta(char *str, int i)
{
	char	*metachars;
	int		j;

	metachars = "<|>()";
	j = 0;
	if (!str || i < 0)
		return (false);
	while (metachars[j] && str[i])
	{
		if (str[i] && str[i] == metachars[j])
			return (true);
		j++;
	}
	return (false);
}