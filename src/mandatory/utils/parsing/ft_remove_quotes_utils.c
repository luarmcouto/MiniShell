/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:48:18 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/27 19:55:53 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_escapable(const char *str, int i, char q, int in_q)
{
	return (in_q && q == '"' && str[i] == '\\'
		&& (str[i + 1] == '$' || str[i + 1] == '"'
			|| str[i + 1] == '\\' || str[i + 1] == '`'));
}

int	count_loop(const char *str, int *in_q, char *q)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (is_escapable(str, i, *q, *in_q))
		{
			len++;
			i += 2;
			continue ;
		}
		process_quote_char(str, i, in_q, q);
		if (!*in_q && str[i] != '\'' && str[i] != '"')
			len++;
		else if (*in_q && str[i] != *q)
			len++;
		i++;
	}
	return (len);
}

void	remove_loop(const char *str, char *res, int *in_q, char *q)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_escapable(str, i, *q, *in_q))
		{
			res[j++] = str[i + 1];
			i += 2;
			continue ;
		}
		if (!skip_quote(str, &i, q, in_q))
			res[j++] = str[i++];
		else
			i++;
	}
	res[j] = '\0';
}
