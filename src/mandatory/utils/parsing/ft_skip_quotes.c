/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:18:46 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:53:32 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * ENGLISH: Skips the current argument in a command string.
 *
 * @param cmd
 *      The command string to process.
 * @param i
 *      Pointer to the index of the current character in the command string.
 */
void	ft_skip_quotes(const char *cmd, int *i)
{
	int		in_quote;
	char	quote;

	in_quote = 0;
	quote = 0;
	while (cmd[*i])
	{
		if (!in_quote && (cmd[*i] == '\'' || cmd[*i] == '"'))
		{
			in_quote = 1;
			quote = cmd[(*i)++];
		}
		else if (in_quote && cmd[*i] == quote)
		{
			in_quote = 0;
			(*i)++;
		}
		else if (!in_quote && ft_isspace(cmd[*i]))
			break ;
		else
			(*i)++;
	}
}

void	ft_init_cmd_argv(t_cmd *cmd, char *arg)
{
	cmd->argv = malloc(2 * sizeof(char *));
	if (cmd->argv)
	{
		cmd->argv[0] = arg;
		cmd->argv[1] = NULL;
	}
}
