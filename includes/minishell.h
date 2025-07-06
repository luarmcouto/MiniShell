#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard libraries */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

/* Readline */
# include <readline/readline.h>
# include <readline/history.h>

/* Libft */
# include "../libft/libft.h"

/* Structs */
typedef struct s_cmd
{
	char			**args;      // ex: {"ls", "-l", NULL}
	char			*path;       // caminho completo para execve
	int				infile;      // descritor de entrada (-1 se não tem)
	int				outfile;     // descritor de saída (-1 se não tem)
	struct s_cmd	*next;       // para pipelines
}	t_cmd;

/* Global variables (only one allowed) */
extern int	g_signal_received;

/* Execution */
void	execute_commands(t_cmd *cmds, char **envp);

/* Built-ins */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd);

/* Utils */
void	free_cmds(t_cmd *cmds);
char	*find_cmd_path(char *cmd, char **envp);
int		ft_strcmp(const char *s1, const char *s2);

/* Temporary function for testing (will be removed when parser is ready) */
t_cmd	*create_test_cmd(char *input);

#endif