/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:08:58 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 18:48:53 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <libft.h>
# include <limits.h>

typedef struct s_shell
{
	t_list		*envp;
	char		**envp_arr;
	t_list		*path; //path_list
	t_list		*token_lst;
	char		*input;
	char		*trim_input;
	void		*root; //binary tree root
	char		*cmd_path;
	char		*cwd;
	int			exit_code;
	int			fd;
}				t_shell;

#endif