/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_stubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:09 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:40:15 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * ltree_print - Stub temporário para impressão da árvore lógica
 * TODO: Implementar na semana de árvore lógica
 */
void	*ltree_print(void *root, int space)
{
	(void)root;
	(void)space;
	printf("    [LOGIC_NODE - not implemented yet]\n");
	return (NULL);
}

/**
 * ltree_free - Stub temporário para liberação da árvore lógica
 * TODO: Implementar na semana de árvore lógica
 */
void	ltree_free(void *root)
{
	// Por enquanto só libera o nó básico
	if (root)
		free(root);
}