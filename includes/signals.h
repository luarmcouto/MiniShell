/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:16:31 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 16:45:57 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

//signals.c
void	sig_main(int signo);
void	set_main_signals(void);
void	handle_signals(void);
void	set_fork1_signal(void);

//signals_heredoc.c
t_shell	*shell_struct(t_shell *shell, int flag);
void	sigint_heredoc_handler(int sig);
void	heredoc_signal(void);

#endif