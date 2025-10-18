/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env_expansion_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:41:17 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:44:03 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <ctype.h>

char	*ft_process_expansion(char *result, char *argv, int *j, t_data *data)
{
	if (argv[*j] != '$')
		return (result);
	if (argv[++(*j)] == '?' && ++(*j))
		return (ft_expand_exit_status(result, data));
	return (ft_expand_env_var(result, argv, j, data));
}
