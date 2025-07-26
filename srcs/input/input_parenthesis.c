/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:35:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/21 21:07:14 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <input.h>

void	balance_message(int balance)
{
	if (balance < 0)
		ft_putendl_fd(CLOSE_ERROR, 2);
	else if (balance > 0)
		ft_putendl_fd(OPEN_ERROR, 2);
}

bool	check_parenthesis(char *str)
{
	int	balance;
	int	i;

	balance = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ')' && balance == 0)
			return (balance_message(-1), false);
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
			balance--;
		i++;
	}
	if (balance != 0)
		balance_message(balance);
	if (balance == 0)
		return (true);
	return (false);
}