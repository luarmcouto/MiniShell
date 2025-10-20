/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/20 10:11:17 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_read_input(char **input, t_data *data)
{
	char	*prompt;

	while (1)
	{
		if (data->isatty)
		{
			prompt = ft_generate_prompt(data->envp);
			*input = readline(prompt);
			free(prompt);
		}
		else
			*input = readline(NULL);
		if (!*input)
			return (0);
		if (**input)
		{
			if (data->isatty)
				add_history(*input);
			return (1);
		}
		free(*input);
	}
}
