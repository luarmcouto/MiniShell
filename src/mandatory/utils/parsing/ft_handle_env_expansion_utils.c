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

static int	is_in_double_quotes(const char *str, int pos)
{
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos && str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_double && !in_single);
}

char	*ft_process_expansion(char *result, char *argv, int *j, t_data *data)
{
	char	*old;
	
	if (argv[*j] != '$')
		return (result);
	if (*j > 0 && argv[*j - 1] == '\\' && is_in_double_quotes(argv, *j))
	{
		old = result;
		result = ft_strjoin(old, "$");
		free(old);
		(*j)++;
		return (result);
	}
	(*j)++;
	if (argv[*j] == '?')
	{
		(*j)++;
		return (ft_expand_exit_status(result, data));
	}
	return (ft_expand_env_var(result, argv, j, data));
}
