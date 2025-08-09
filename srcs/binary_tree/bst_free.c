/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:37:41 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:39:02 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * free_bst - Libera toda a árvore binária
 * @root: raiz da árvore
 * 
 * Função principal para limpeza de memória da árvore.
 * Identifica o tipo de nó e chama a função apropriada.
 */
void	free_bst(void *root)
{
	t_node	*node;

	if (!root)
		return ;
	
	node = (t_node *)root;
	
	if (node->type == N_PIPE)
		free_pipe_children((t_pipe *)root);
	else if (node->type == N_EXEC)
		free_exec((t_exec *)root);
	else if (node->type == N_ANDIF)
		ltree_free((t_andif *)root);
	else if (node->type == N_OR)
		ltree_free((t_or *)root);
	
	return ;
}

/**
 * free_pipe_children - Libera nó pipe e seus filhos
 * @pipe: nó pipe a ser liberado
 * 
 * Recursivamente libera os nós filhos antes de liberar o pipe
 */
void	free_pipe_children(t_pipe *pipe)
{
	if (pipe)
	{
		if (pipe->left)
			ltree_free(pipe->left);
		if (pipe->right)
			ltree_free(pipe->right);
	}
	free(pipe);
}

/**
 * free_inf - Libera estrutura de arquivo de entrada
 * @content: conteúdo da lista (t_inf)
 * 
 * Função de callback para ft_lstclear
 */
void	free_inf(void *content)
{
	const t_inf	*infile = (t_inf *)content;

	if (infile)
	{
		free(infile->name);
		free(infile->eof);
		free((void *)infile);
	}
}

/**
 * free_outf - Libera estrutura de arquivo de saída
 * @content: conteúdo da lista (t_outf)
 * 
 * Função de callback para ft_lstclear
 */
void	free_outf(void *content)
{
	const t_outf	*outfile = (t_outf *)content;

	if (outfile)
	{
		free(outfile->name);
		free((void *)outfile);
	}
}

/**
 * free_exec - Libera nó exec completamente
 * @node: nó exec a ser liberado
 * 
 * Libera todos os componentes de um nó de execução:
 * - Array de argumentos
 * - Lista de arquivos de entrada
 * - Lista de arquivos de saída
 * - O nó em si
 */
/**
 * free_exec - Libera nó exec completamente
 * @node: nó exec a ser liberado
 * 
 * Libera todos os componentes de um nó de execução:
 * - Array de argumentos
 * - Lista de arquivos de entrada
 * - Lista de arquivos de saída
 * - O nó em si
 */
void	free_exec(t_exec *node)
{
	if (node)
	{
		// Libera array de argumentos
		if (node->argv)
		{
			free(node->argv);
		}
		
		// Libera lista de infiles
		if (node->infiles)
		{
			ft_lstclear(&node->infiles, free_inf);
		}
		free(node->infiles);
		
		// Libera lista de outfiles
		if (node->outfiles)
		{
			ft_lstclear(&node->outfiles, free_outf);
		}
		free(node->outfiles);
		
		// Libera o nó
		free(node);
	}
}
