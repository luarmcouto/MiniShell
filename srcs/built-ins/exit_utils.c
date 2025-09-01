/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/01 18:09:18 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	g_exit_code = 0;

int	get_exit_code(int new_code)
{
	if (new_code >= 0)
		g_exit_code = new_code;
	return (g_exit_code);
}

// Função placeholder para export (será implementada no domingo)
int	export_variable(t_shell *shell_data, const char *arg_str)
{
	(void)shell_data;
	(void)arg_str;
	// TODO: Implementar export no domingo
	return (0);
}

// Função placeholder para exit (será implementada no domingo)
void	builtin_exit(t_shell *shell_data, t_exec *cmd_node)
{
	(void)shell_data;
	(void)cmd_node;
	// TODO: Implementar exit no domingo
	printf("exit\n");
	exit(0);
}

// Função placeholder para unset (será implementada no domingo)
void	builtin_unset(t_shell *shell_data, char **arguments)
{
	(void)shell_data;
	(void)arguments;
	// TODO: Implementar unset no domingo
	printf("minishell: unset: not implemented yet\n");
}
