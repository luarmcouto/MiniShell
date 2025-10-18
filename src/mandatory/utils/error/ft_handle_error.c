/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:27:37 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:13:44 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../mandatory/minishell.h"
#include <stdlib.h>

static void	ft_print_error_no_params(int error_code)
{
	if (error_code == 2)
		ft_fprintf(2, ERROR_PERMISSION_DENIED);
	else if (error_code == 5)
		ft_fprintf(2, ERROR_SYNTAX);
	else if (error_code == 7)
		ft_fprintf(2, ERROR_TOO_MANY_ARGS);
	else if (error_code == 8)
		ft_fprintf(2, ERROR_HOME_NOT_SET);
	else if (error_code == 9)
		ft_fprintf(2, ERROR_HEREDOC_DELIMITER);
	else if (error_code == 10)
		ft_fprintf(2, ERROR_HEREDOC_PROCESS);
}

static void	ft_print_error_with_params(int code, char *msg, char *msg2)
{
	if (code == 1)
		ft_fprintf(2, ERROR_COMMAND_NOT_FOUND, msg);
	else if (code == 3)
		ft_fprintf(2, ERROR_IS_A_DIRECTORY, msg);
	else if (code == 4)
		ft_fprintf(2, ERROR_NO_SUCH_FILE, msg);
	else if (code == 6)
		ft_fprintf(2, ERROR_SYNTAX_TOKEN, msg);
	else if (code == 11)
		ft_fprintf(2, ERROR_CD_FAIL, msg, msg2);
	else if (code == 12)
		ft_fprintf(2, ERROR_AMBIGUOUS_REDIRECT, msg);
	else if (code == 13)
		ft_fprintf(2, ERROR_INVALID_IDENTIFIER, msg);
	else if (code == 14)
		ft_fprintf(2, ERROR_NUM_ARG_REQ, msg);
}

int	ft_handle_error(int error_code, int exit_code, char *msg, char *msg2)
{
	if (error_code == 2 || error_code == 5 || error_code == 7
		|| error_code == 8 || error_code == 9 || error_code == 10)
		ft_print_error_no_params(error_code);
	else
		ft_print_error_with_params(error_code, msg, msg2);
	return (exit_code);
}
