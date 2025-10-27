/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:16:59 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/27 19:58:28 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_quote(const char *str, int *i, char *quote, int *in_quote)
{
	if (!*in_quote && (str[*i] == '\'' || str[*i] == '"'))
	{
		*in_quote = 1;
		*quote = str[*i];
		return (1);
	}
	else if (*in_quote && str[*i] == *quote)
	{
		*in_quote = 0;
		*quote = 0;
		return (1);
	}
	return (0);
}

void	process_quote_char(const char *str, int i, int *in_q, char *q)
{
	if ((!*in_q && (str[i] == '\'' || str[i] == '"')))
	{
		*in_q = 1;
		*q = str[i];
	}
	else if (*in_q && str[i] == *q)
	{
		*in_q = 0;
		*q = 0;
	}
}

static int	calc_unquoted_len(const char *str)
{
	int		in_q;
	char	q;

	in_q = 0;
	q = 0;
	return (count_loop(str, &in_q, &q));
}

static void	init_remove_quotes_vars(int *i, int *j, int *in_q, char *q)
{
	*i = 0;
	*j = 0;
	*in_q = 0;
	*q = 0;
}

char	*ft_remove_quotes(const char *str)
{
	int		i;
	char	q;
	char	*res;
	int		j;
	int		in_q;

	if (!str)
		return (NULL);
	init_remove_quotes_vars(&i, &j, &in_q, &q);
	res = malloc(calc_unquoted_len(str) + 1);
	if (!res)
		return (NULL);
	remove_loop(str, res, &in_q, &q);
	return (res);
}
