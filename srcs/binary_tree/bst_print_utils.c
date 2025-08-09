/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:07:46 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:20:44 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * print_bst_exec - Imprime nó de execução completo
 * @node: nó exec a imprimir
 * @space: espaçamento para indentação
 * 
 * Mostra todos os componentes de um comando:
 * - Arquivos de saída (se houver)
 * - O comando EXEC
 * - Argumentos
 * - Arquivos de entrada (se houver)
 */
void	print_bst_exec(t_exec *node, int space)
{
	int	i;

	i = 0;
	
	// Imprime outfiles primeiro
	if (node->outfiles)
		print_outfiles(node->outfiles, space);
	
	// Imprime identificação do nó EXEC
	while (i < space)
	{
		printf(" ");
		i++;
	}
	printf("[EXEC]\n");
	
	// Imprime argumentos do comando
	if (node->argv)
	{
		print_exec(node->argv, space);
	}
	
	// Imprime infiles por último
	if (node->infiles)
		print_infiles(node->infiles, space);
}

/**
 * print_outfiles - Imprime lista de arquivos de saída
 * @outfiles: lista de t_outf
 * @space: espaçamento para indentação
 * 
 * Mostra todos os redirecionamentos de saída
 */
void	print_outfiles(t_list *outfiles, int space)
{
	int	i;

	i = 0;
	while (i < space + 2)
	{
		printf(" ");
		i++;
	}
	printf("[OUTFILES]: ");
	
	i = 0;
	while (outfiles)
	{
		printf("%s", (char *)((t_outf *)outfiles->content)->name);
		if (outfiles->next)
			printf(", ");
		outfiles = outfiles->next;
	}
	printf("\n");
}

/**
 * print_exec - Imprime argumentos do comando
 * @argv: array de argumentos
 * @space: espaçamento para indentação
 * 
 * Mostra cada argumento em uma linha separada
 */
void	print_exec(char **argv, int space)
{
	int	i;
	int	j;

	j = 0;
	while (argv[j])
	{
		i = 0;
		while (i < space + 2)
		{
			printf(" ");
			i++;
		}
		printf("[%s]\n", argv[j]);
		j++;
	}
}

/**
 * print_infiles - Imprime lista de arquivos de entrada
 * @infiles: lista de t_inf
 * @space: espaçamento para indentação
 * 
 * Mostra todos os redirecionamentos de entrada
 */
void	print_infiles(t_list *infiles, int space)
{
	int	i;

	i = 0;
	while (i < space + 2)
	{
		printf(" ");
		i++;
	}
	printf("[INFILES]: ");
	
	i = 0;
	while (infiles)
	{
		printf("%s", (char *)((t_inf *)infiles->content)->eof);
		if (infiles->next)
			printf(", ");
		infiles = infiles->next;
	}
	printf("\n");
}