#include "minishell.h"

// Função para configurar redirecionamento de entrada
int	setup_input_redirect(char *filename)
{
	int	fd;

	if (!filename)
		return (-1);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}

	// Duplica o file descriptor para stdin
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}

	close(fd);
	return (0);
}

// Função para configurar redirecionamento de saída
int	setup_output_redirect(char *filename, int append_mode)
{
	int	fd;
	int	flags;

	if (!filename)
		return (-1);

	// Define as flags baseado no modo
	if (append_mode)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}

	// Duplica o file descriptor para stdout
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}

	close(fd);
	return (0);
}

// Função para aplicar todos os redirecionamentos de um comando
int	apply_redirections(t_cmd *cmd)
{
	// Por enquanto, vamos usar campos simples
	// TODO: Expandir quando o parser passar mais informações sobre redirecionamentos
	
	if (!cmd)
		return (-1);

	// Se há redirecionamento de entrada
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			return (-1);
		}
		close(cmd->infile);
	}

	// Se há redirecionamento de saída
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			return (-1);
		}
		close(cmd->outfile);
	}

	return (0);
}

// Função para processar redirecionamentos do parsing
// Esta será chamada durante o parsing para abrir os arquivos
int	process_redirection_token(t_cmd *cmd, char *filename, t_token_type type)
{
	int	fd;

	if (!cmd || !filename)
		return (-1);

	switch (type)
	{
		case TOKEN_REDIRECT_IN:
			// < arquivo
			fd = open(filename, O_RDONLY);
			if (fd == -1)
			{
				perror(filename);
				return (-1);
			}
			if (cmd->infile != -1)
				close(cmd->infile);
			cmd->infile = fd;
			break;

		case TOKEN_REDIRECT_OUT:
			// > arquivo
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(filename);
				return (-1);
			}
			if (cmd->outfile != -1)
				close(cmd->outfile);
			cmd->outfile = fd;
			break;

		case TOKEN_APPEND:
			// >> arquivo
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(filename);
				return (-1);
			}
			if (cmd->outfile != -1)
				close(cmd->outfile);
			cmd->outfile = fd;
			break;

		default:
			return (-1);
	}

	return (0);
}