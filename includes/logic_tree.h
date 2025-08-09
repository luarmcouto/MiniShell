/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:11:12 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/09 09:11:12 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGIC_TREE_H
# define LOGIC_TREE_H

# include <binary_tree.h>

typedef struct s_andif
{
	t_node	type;
	void	*left;
	void	*right;
}				t_andif;

typedef struct s_or
{
	t_node	type;
	void	*left;
	void	*right;
}				t_or;

/* ====== LOGIC TREE CORE ====== */

// build_ltree.c
void	*build_ltree(t_shell *shell, t_list *token_list);
void	*insert_lnode(t_shell *shell, void *lnode, t_list *token_lst);
void	*create_subtree(t_shell *shell, t_list *token_lst);
void	*create_and(t_shell *shell, void *left, void *right);
void	*create_or(t_shell *shell, void *left, void *right);

// build_ltree_utils.c
int		check_token(t_list *node);

// ltree_parenthesis.c
t_list	*new_sublist(t_list *t_lst);
void	clean_sublist(t_list *new);
void	*get_andif_subnode(t_shell *shell, void *l_node, t_list *t_lst);
void	*get_or_subnode(t_shell *shell, void *l_node, t_list *t_lst);
bool	is_parenthesis(t_list *t_lst);

// ltree_parenthesis2.c
void	*start_parenthesis(t_shell *shell, t_list *t_lst, void *l_node);
t_list	*jump_parenthesis(t_list *tmp);
void	*get_pipe_subnode(t_shell *shell, void *l_node, t_list *t_lst);
t_list	*get_new_token(t_list *tmp);

// ltree_print.c
void	*ltree_print(void *root, int space);
void	ltree_free(void *root);

#endif