/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:35:06 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/17 20:16:30 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_build_path(const char *dir, const char *entry)
{
	size_t	dir_len;
	size_t	entry_len;
	size_t	total_len;
	char	*path;

	dir_len = ft_strlen(dir);
	entry_len = ft_strlen(entry);
	total_len = dir_len + 1 + entry_len + 1;
	path = malloc(total_len);
	if (!path)
		return (NULL);
	ft_memcpy(path, dir, dir_len);
	path[dir_len] = '/';
	ft_memcpy(path + dir_len + 1, entry, entry_len);
	path[dir_len + 1 + entry_len] = '\0';
	return (path);
}
