/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:13:17 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/09 09:13:17 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * print_tree_structure - Imprime estrutura da árvore para debug
 * @root: raiz da árvore
 * 
 * Função de debug para visualizar estrutura da árvore binária/lógica
 */
void	print_tree_structure(void *root)
{
	printf("\n🌳 === TREE STRUCTURE DEBUG ===\n");
	
	if (!root)
	{
		printf("❌ Tree is NULL\n");
		return ;
	}
	
	// TODO: Implementar quando tivermos as estruturas da árvore
	printf("✅ Tree root exists\n");
	printf("📊 Tree analysis will be implemented in week 3\n");
	printf("==============================\n\n");
}

/**
 * validate_tree_integrity - Valida integridade da árvore
 * @root: raiz da árvore
 * 
 * Verifica se a estrutura da árvore está correta
 */
void	validate_tree_integrity(void *root)
{
	printf("\n🔍 === TREE INTEGRITY CHECK ===\n");
	
	if (!root)
	{
		printf("❌ Cannot validate NULL tree\n");
		return ;
	}
	
	// TODO: Implementar validações específicas
	printf("✅ Basic validation passed\n");
	printf("🚧 Full validation will be implemented in week 3\n");
	printf("=============================\n\n");
}

/**
 * print_parenthesis_balance - Verifica balanceamento de parênteses
 * @token_lst: lista de tokens
 */
void	print_parenthesis_balance(t_list *token_lst)
{
	t_token	*token;
	int		balance;
	int		total_open;
	int		total_close;

	balance = 0;
	total_open = 0;
	total_close = 0;
	
	printf("\n🔗 === PARENTHESIS BALANCE ===\n");
	
	while (token_lst)
	{
		token = (t_token *)token_lst->content;
		
		if (token->type == PARENTHESIS)
		{
			if (ft_strcmp(token->value, "(") == 0)
			{
				balance++;
				total_open++;
			}
			else if (ft_strcmp(token->value, ")") == 0)
			{
				balance--;
				total_close++;
			}
		}
		
		token_lst = token_lst->next;
	}
	
	printf("Opening parentheses: %d\n", total_open);
	printf("Closing parentheses: %d\n", total_close);
	printf("Final balance: %d\n", balance);
	
	if (balance == 0)
		printf("✅ Parentheses are balanced\n");
	else
		printf("❌ Parentheses are NOT balanced\n");
	
	printf("===========================\n\n");
}

/**
 * debug_command_structure - Debug da estrutura de comando
 * @token_lst: lista de tokens
 */
void	debug_command_structure(t_list *token_lst)
{
	t_token	*token;
	bool	has_command;
	bool	has_args;
	bool	has_pipes;
	bool	has_redirs;

	has_command = false;
	has_args = false;
	has_pipes = false;
	has_redirs = false;
	
	printf("\n📋 === COMMAND STRUCTURE ===\n");
	
	while (token_lst)
	{
		token = (t_token *)token_lst->content;
		
		if (token->type == WORD && !has_command)
			has_command = true;
		else if (token->type == WORD && has_command)
			has_args = true;
		else if (token->type == PIPE)
			has_pipes = true;
		else if (token->type == INFILE || token->type == OUTFILE ||
				token->type == APPEND || token->type == HEREDOC)
			has_redirs = true;
		
		token_lst = token_lst->next;
	}
	
	printf("Has command: %s\n", has_command ? "✅ Yes" : "❌ No");
	printf("Has arguments: %s\n", has_args ? "✅ Yes" : "❌ No");
	printf("Has pipes: %s\n", has_pipes ? "✅ Yes" : "❌ No");
	printf("Has redirections: %s\n", has_redirs ? "✅ Yes" : "❌ No");
	printf("=========================\n\n");
}