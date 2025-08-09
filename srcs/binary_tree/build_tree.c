/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:40:38 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:48:27 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * build_tree - Constrói a árvore binária principal para execução
 * @shell: estrutura principal do shell
 * @token_list: lista de tokens para processar
 * 
 * Esta função é o coração do sistema de parsing. Ela converte
 * a lista linear de tokens em uma árvore binária que representa
 * a estrutura hierárquica dos comandos e suas conexões.
 * 
 * Return: ponteiro para a raiz da árvore
 */
void	*build_tree(t_shell *shell, t_list *token_list)
{
	t_list	*tmp;
	void	*root;

	tmp = token_list;
	root = NULL;
	
	// Processa todos os tokens, criando nós da árvore
	while (check_token(tmp))
	{
		root = insert_node(shell, root, tmp);
		
		// Navega pela lista baseado no tipo de token
		if (((t_token *)tmp->content)->type != PIPE)
		{
			tmp = skip_if(tmp);
		}
		else
		{
			tmp = skip_else(tmp);
		}
	}
	return (root);
}

/**
 * insert_node - Insere um novo nó na árvore
 * @shell: estrutura principal do shell
 * @node: nó atual da árvore
 * @token_lst: lista de tokens a partir da posição atual
 * 
 * Cria nós de pipe ou exec baseado na estrutura dos tokens
 * 
 * Return: ponteiro para o nó criado/atualizado
 */
void	*insert_node(t_shell *shell, void *node, t_list *token_lst)
{
	t_pipe	*pipe;

	// Se não há nó, cria um nó exec
	if (!node)
		return (create_exec(shell, token_lst));
	
	// Se há nó, cria um pipe conectando o nó existente ao novo
	pipe = create_pipe(shell, node, create_exec(shell, token_lst->next));
	return (pipe);
}

/**
 * create_exec - Cria um nó de execução
 * @shell: estrutura principal do shell
 * @token_lst: lista de tokens a processar
 * 
 * Nó exec representa um comando simples com seus argumentos,
 * redirecionamentos de entrada e saída.
 * 
 * Return: ponteiro para o nó exec criado
 */
void	*create_exec(t_shell *shell, t_list *token_lst)
{
	t_exec	*node;
	t_list	*current;

	if (!token_lst)
		return (NULL);
	
	// Aloca e inicializa o nó exec
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		exit_failure(shell, "create_exec");
	
	node->type.type = N_EXEC;
	node->infiles = NULL;
	node->command = NULL;
	node->argv = NULL;
	node->outfiles = NULL;
	
	// Extrai informações dos tokens
	get_infiles(shell, token_lst, &node->infiles);
	get_outfiles(shell, token_lst, &node->outfiles);
	
	// Encontra o comando principal
	current = get_name(token_lst);
	if (current)
	{
		node->command = ((t_token *)current->content)->value;
		node->argv = get_argv(shell, token_lst);
		
		// Adiciona cores para ls e grep automaticamente
		if (ft_strcmp(node->argv[0], "ls") == 0
			|| ft_strcmp(node->argv[0], "grep") == 0)
			node->argv = get_colors(shell, node->argv);
	}
	
	return (node);
}

/**
 * create_pipe - Cria um nó de pipe
 * @shell: estrutura principal do shell
 * @left: nó filho esquerdo
 * @right: nó filho direito
 * 
 * Nó pipe conecta dois comandos através de pipe Unix,
 * onde a saída do left vira entrada do right.
 * 
 * Return: ponteiro para o nó pipe criado	
 */
void	*create_pipe(t_shell *shell, void *left, void *right)
{
	t_pipe	*node;

	node = (t_pipe *)malloc(sizeof(t_pipe));
	if (!node)
		exit_failure(shell, "create_pipe");
	
	node->type.type = N_PIPE;
	node->left = left;
	node->right = right;
	
	return (node);
}

/**
 * get_name - Encontra o token que representa o comando principal
 * @tkn_lst: lista de tokens
 * 
 * Percorre a lista ignorando redirecionamentos e argumentos,
 * encontrando a primeira palavra que será o comando.
 * 
 * Return: ponteiro para o token do comando ou NULL
 */
t_list	*get_name(t_list *tkn_lst)
{
	t_list	*word;

	word = NULL;
	while (tkn_lst && (((t_token *)tkn_lst->content)->type != PIPE))
	{
		// Pula redirecionamentos de entrada
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
				|| ((t_token *)tkn_lst->content)->type == HEREDOC))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		
		// Pula redirecionamentos de saída
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == OUTFILE
				|| ((t_token *)tkn_lst->content)->type == APPEND))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		
		// Encontrou uma palavra válida
		if (tkn_lst && ((t_token *)tkn_lst->content)->type == WORD
			&& ((t_token *)tkn_lst->content)->state != EXPAND)
			return (tkn_lst);
		
		tkn_lst = tkn_lst->next;
		
		// Para em operadores lógicos
		if (tkn_lst && ((t_token *)tkn_lst->content)->type == AND_IF)
			break ;
	}
	return (word);
}