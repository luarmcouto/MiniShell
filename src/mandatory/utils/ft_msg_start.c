/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:58:40 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/17 20:21:09 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_msg_start(void)
{
	char	*welcome_msg;

	welcome_msg = ft_search_file(NULL, "welcome.txt");
	ft_putstr("\x1B" "c");
	if (welcome_msg)
	{
		ft_print_file(welcome_msg, COLOR_MAGENTA);
		free(welcome_msg);
	}
	else
		ft_print_file(WELCOME_MSG_TXT, COLOR_MAGENTA);
	ft_putstr("\n");
	ft_putstr(WELCOME_TEXT);
	ft_putstr("\n\n");
	return (0);
}
