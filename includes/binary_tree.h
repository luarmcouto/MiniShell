/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:53:24 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:33:01 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include <structs.h>

typedef enum e_node_type
{
	N_PIPE,
	N_EXEC,
	N_ANDIF,
	N_OR,
}				t_node_type;

typedef struct s_node
{
	t_node_type	type;
}				t_node;

typedef struct s_pipe
{
	t_node			type;
	struct s_exec	*left;
	struct s_exec	*right;
}				t_pipe;

typedef enum e_inf_t
{
	INF,
	HERE,
}				t_inf_t;

typedef struct s_inf
{
	t_inf_t	type;
	char	*eof;
	char	*name;
}				t_inf;

typedef enum e_outf_t
{
	APP,
	ADD,
}				t_outf_t;

typedef struct s_outf
{
	t_outf_t	type;
	char		*name;
}				t_outf;

typedef struct s_exec
{
	t_node		type;
	char		*command;
	char		**argv;
	t_list		*infiles;
	t_list		*outfiles;
}				t_exec;

// Estruturas para árvore lógica (bonus)
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

//bst_free.c
void	free_bst(void *root);
void	free_pipe_children(t_pipe *pipe);
void	free_exec(t_exec *node);
void	free_inf(void *content);
void	free_outf(void *content);

//bst_print.c
void	*print_bst(void *root, int space);
void	print_pipe_children(t_pipe *pipe, int space);
void	print_bst_pipe(t_pipe *node, int space);
void	print_bst_exec(t_exec *node, int space);

//bst_print_utils.c
void	print_bst_exec(t_exec *node, int space);
void	print_outfiles(t_list *outfiles, int space);
void	print_exec(char **argv, int space);
void	print_infiles(t_list *infiles, int space);

//build_tree.c
void	*build_tree(t_shell *shell, t_list *token_list);
void	*insert_node(t_shell *shell, void *node, t_list *token_lst);
void	*create_pipe(t_shell *shell, void *left, void *right);
void	*create_exec(t_shell *shell, t_list *token_lst);
t_list	*get_name(t_list *tkn_lst);

//build_tree_utils.c
char	**get_argv(t_shell *shell, t_list *token_lst);
t_list	*get_infiles(t_shell *shell, t_list *token_lst, t_list **infiles);
t_list	*get_outfiles(t_shell *shell, t_list *token_lst, t_list **outfiles);
char	**get_colors(t_shell *shell, char **argv);
int		count_args(t_list *tkn_lst);

//build_tree_utils2.c
t_list	*skip_if(t_list *tmp);
t_list	*skip_else(t_list *tmp);
t_list	*check_word(t_list **current, char **argv, int *i);
t_list	*check_w_args(t_list *tkn_lst, int *args);

//ltree_functions (temporary stubs)
void	*ltree_print(void *root, int space);
void	ltree_free(void *root);

#endif