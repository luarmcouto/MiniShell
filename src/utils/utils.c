#include "minishell.h"

static char	*get_env_value(char *name, char **envp)
{
	int		i;
	int		name_len;

	if (!name || !envp)
		return (NULL);
	
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static char	*check_executable(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (ft_strdup(path));
		else
		{
			printf("minishell: %s: Permission denied\n", path);
			return (NULL);
		}
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	if (!cmd)
		return (NULL);

	// Se já é um caminho absoluto ou relativo
	if (ft_strchr(cmd, '/'))
		return (check_executable(cmd));

	// Busca no PATH
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (NULL);

	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	i = 0;
	while (paths[i])
	{
		// Constrói caminho completo: path + "/" + cmd
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			// Libera paths já alocados
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (NULL);
		}
		
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		
		if (!full_path)
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (NULL);
		}

		// Verifica se existe e é executável
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			// Libera o array de paths
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		
		free(full_path);
		i++;
	}

	// Libera o array de paths
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);

	return (NULL);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = cmds;
	while (current)
	{
		next = current->next;
		
		// Libera array de argumentos
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		
		// Libera path se foi alocado
		if (current->path)
			free(current->path);
		
		// Fecha file descriptors se não são stdin/stdout/stderr
		if (current->infile != STDIN_FILENO && current->infile != -1)
			close(current->infile);
		if (current->outfile != STDOUT_FILENO && current->outfile != -1)
			close(current->outfile);
		
		free(current);
		current = next;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}