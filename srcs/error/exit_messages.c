/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_messages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:11:45 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/16 19:12:20 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * is_directory - Implementação usando função existente de errors
 * A função is_directory já existe em exit_messages.c, mas com assinatura diferente.
 * Vamos fazer um wrapper para manter compatibilidade.
 */
void	is_directory(t_shell *shell, char **argv)
{
	// A função original retorna int e recebe char **path
	// Aqui fazemos um wrapper para manter compatibilidade
	(void)shell;
	(void)argv;
	// TODO: Integrar com função existente quando necessário
}