/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:59:10 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:59:10 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H
# define UTILS_H

# include <structs.h>

// string_utils.c
char	*ft_strjoin_free(char *s1, char *s2);
int     ft_isspace(char c);
int	ft_flag(char c, int *i, bool flag);

// debug_utils.c
void	print_tokens(t_list *token_lst);
void	print_token_details(t_token *token);
void	analyze_token_sequence(t_list *token_lst);

// tree_debug.c (preparação para próximas semanas)
void	print_tree_structure(void *root);
void	validate_tree_integrity(void *root);
void	print_parenthesis_balance(t_list *token_lst);
void	debug_command_structure(t_list *token_lst);

// array_utils.c
int		ft_arrlen(char **arr);

// ft_split_utils.c
char	**ft_split(char const *s, char c);
void	ft_free_array(char **array);

// Função para expansão
bool	is_expandable(char *token);
char	*handle_expand(t_shell *shell, char *input, int i);

#endif