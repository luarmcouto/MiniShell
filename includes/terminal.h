/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:19:41 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 15:46:34 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <structs.h>

//terminal.c
void	terminal(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
void	prepare_shell(t_shell *shell, char **envp);
void	execute_command(t_shell *shell, int *status);
int		is_env_empty(t_shell *shell);

//terminal_utils.c
void	shell_input(t_shell *shell);
void	exec_processes(t_shell *shell, void *root);
int		is_env_empty(t_shell *shell);
void	reset_shell(t_shell *shell);

#endif