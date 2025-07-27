/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_sizes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:59:43 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 15:33:37 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	content_size(char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[j] && env[j] != '\0')
		j++;
	return (j - i);
}

int	val_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	return (i);
}