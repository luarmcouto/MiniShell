/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:40:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/21 21:08:18 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <input.h>

bool	check_line_len(char *line)
{
	if (ft_strlen(line) > 200)
		return (ft_putendl_fd(LINE_ERROR, 2), false);
	return (true);
}