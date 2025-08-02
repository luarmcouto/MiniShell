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
int		ft_isspace(char c);
char	*ft_strndup(const char *s, size_t n);
int		ft_array_len(char **array);
void	ft_free_array(char **array);

// debug_utils.c
void	print_tokens(t_list *token_lst);

#endif