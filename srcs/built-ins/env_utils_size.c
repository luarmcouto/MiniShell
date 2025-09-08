/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:59:43 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 18:15:27 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_content_size(char *env_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	i++;
	while (env_str[j] && env_str[j] != '\0')
		j++;
	return (j - i);
}

int	get_value_size(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	i++;
	return (i);
}