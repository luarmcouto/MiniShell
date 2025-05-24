#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard libraries */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Readline */
# include <readline/readline.h>
# include <readline/history.h>

/* Libft */
# include "../libft/libft.h"

/* Structs */
typedef struct s_cmd
{
	char	**args;      // ex: {"ls", "-l", NULL}
	char	*path;      // caminho completo para execve
	int		infile;     // descritor de entrada
	int		outfile;    // descritor de saída
	struct s_cmd *next; // para pipelines
}	t_cmd;

/* Execution */
void	execute_commands(t_cmd *cmds, char **envp);

/* Built-ins */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd);

/* Utils */
void	free_cmds(t_cmd *cmds);
char	*find_cmd_path(char *cmd, char **envp);

#endif
