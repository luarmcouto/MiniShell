/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:56:02 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:56:02 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_balance(char *input, int i)
{
	int	balance;

	balance = 1;
	while (input[i] && balance != 0)
	{
		i++;
		if (input[i] && input[i] == '(')
			balance++;
		if (input[i] && input[i] == ')')
			balance--;
	}
	return (i);
}

int	set_hered(t_shell *sh, t_token *new_token, char *input, int i)
{
	new_token->value = ft_substr(input, i, 2);
	if (!new_token->value)
		exit_failure(sh, "set_hered");
	new_token->type = HEREDOC;
	return (i + 2);
}