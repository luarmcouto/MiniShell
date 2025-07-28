/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:56:36 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:56:36 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}