/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:58:42 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:58:42 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

int ft_isspace(char c)
{
    return (c == ' '  ||  // espaço
            c == '\t' ||  // tabulação horizontal
            c == '\n' ||  // nova linha
            c == '\v' ||  // tabulação vertical
            c == '\f' ||  // form feed
            c == '\r');   // carriage return
}