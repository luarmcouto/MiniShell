/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:18:50 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/22 19:27:40 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_args(int argc, char *argv[], char *envp[])
{
	(void) argv;
	if (!envp || !*envp)
	{
		ft_putendl_fd(RED"WARNING: env -i"DEFAULT, 2);
	}
	if (argc > 1)
	{
		ft_putendl_fd(RED"Invalid input"DEFAULT, 2);
		exit(1);
	}
	return (0);
}