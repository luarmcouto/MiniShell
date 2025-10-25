/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_in_subdirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:24:06 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/20 13:33:12 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_search_in_subdir_utils(const char *dir, const char *entry_name,
	const char *filename)
{
	char	*sub_path;
	char	*result;
	DIR		*subdir;

	result = NULL;
	sub_path = ft_build_path(dir, entry_name);
	subdir = opendir(sub_path);
	if (subdir)
	{
		closedir(subdir);
		result = ft_search_file(sub_path, filename);
	}
	free(sub_path);
	return (result);
}

static char	*ft_search_entries(DIR *d, const char *dir, const char *filename)
{
	struct dirent	*entry;
	char			*result;

	result = NULL;
	entry = readdir(d);
	while (entry)
	{
		if (ft_is_dot_or_dotdot(entry->d_name))
		{
			entry = readdir(d);
			continue ;
		}
		result = ft_search_in_subdir_utils(dir, entry->d_name, filename);
		if (result)
			break ;
		entry = readdir(d);
	}
	return (result);
}

char	*ft_search_in_subdirs(const char *dir, const char *filename)
{
	DIR		*d;
	char	*result;

	result = NULL;
	d = opendir(dir);
	if (!d)
		return (NULL);
	result = ft_search_entries(d, dir, filename);
	closedir(d);
	return (result);
}
