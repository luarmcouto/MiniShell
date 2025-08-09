/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 08:54:20 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:20:22 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * print_bst - Imprime a árvore binária de forma visual
 * @root: raiz da árvore
 * @space: espaçamento para indentação
 * 
 * Função principal para visualizar a estrutura da árvore.
 * Útil para debug e compreensão da estrutura criada.
 * 
 * Return: NULL (função de debug)
 */
void	*print_bst(void *root, int space)
{
	t_node	*node;
	int		spacing;

	if (space == 5)
		printf("\n\n\nTREE VIEW:\n");
	
	spacing = 5;
	space += spacing;
	
	if (!root)
		return (NULL);
	
	node = (t_node *)root;
	
	if (node->type == N_PIPE)
		print_pipe_children((t_pipe *)root, space);
	else if (node->type == N_EXEC)
		print_bst_exec((t_exec *)root, space);
	else if (node->type == N_ANDIF)
		ltree_print((t_andif *)root, space);
	else if (node->type == N_OR)
		ltree_print((t_or *)root, space);
	
	return (NULL);
}

/**
 * print_pipe_children - Imprime nó pipe e seus filhos
 * @pipe: nó pipe a imprimir
 * @space: espaçamento atual
 * 
 * Imprime primeiro o filho direito, depois o pipe, depois o esquerdo
 * para mostrar a árvore de forma rotacionada
 */
void	print_pipe_children(t_pipe *pipe, int space)
{
	if (pipe->right)
		print_bst(pipe->right, space);
	
	print_bst_pipe(pipe, space);
	
	if (pipe->left)
		print_bst(pipe->left, space);
}

/**
 * print_bst_pipe - Imprime o símbolo do pipe
 * @node: nó pipe
 * @space: espaçamento para indentação
 * 
 * Mostra visualmente onde está o pipe na árvore
 */
void	print_bst_pipe(t_pipe *node, int space)
{
	int	i;

	i = 0;
	printf("\n");
	
	while (i < space)
	{
		printf(" ");
		i++;
	}
	
	if (node->type.type == N_PIPE)
		printf("[PIPE]\n");
}