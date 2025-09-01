/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:12:46 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/21 15:12:46 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Checar protótipos que estão aqui ou em outros .h, porém a função já não está mais em uso

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <structs.h>
# include <colors.h>
# include <terminal.h>
# include <input.h>
# include <signal.h>
# include <signals.h>
# include <binary_tree.h>
# include <builtins.h>
# include <tokenization.h>
# include <utils.h>
# include <exec.h>
# include <logic_tree.h>


// MACROS
# define ESC_START "\001\033[1;91m\002"
# define ESC_RESET "\001\033[0;93m\002"
# define PROMPT "Minishell ["
# define ESC_CODE "\001\033[1;91m\002] [\001\033[0;39m\002"
# define ARROW "\001\033[1;91m]\002 \001→\002\001\033[0m\002  \b"
# define MINISHELL "\001\033[0;93\002mminishell\001\033[0;39m\002"

/*metacharaters
 * A character that, when unquoted, separates words. A metacharacter is a space
 * , tab, newline, or one of the following characters:
 * '|', '&', ';', '(', ')', '<', or '>'
*/
# define METACHARS "|;<>"

//check_args.c
int	check_args(int argc, char *argv[], char *envp[]);

#endif