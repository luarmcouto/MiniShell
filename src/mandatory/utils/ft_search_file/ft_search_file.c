/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:22:57 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/17 20:16:42 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_search_file(const char *dir, const char *filename)
{
	const char	*start_dir;

	if (dir)
		start_dir = dir;
	else
		start_dir = getenv("PWD");
	return (ft_search_in_dir(start_dir, filename));
}
