/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 19:48:45 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*ft_read_heredoc_line(void)
{
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	if (isatty(STDIN_FILENO))
		write(1, HEREDOC_PROMPT, 9);
	nread = getline(&line, &len, stdin);
	if (nread == -1 || !line)
		return (NULL);
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

static int	ft_check_delimiter(char *line, const char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

static void	ft_write_heredoc_line(int fd, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	line[len] = '\n';
	write(fd, line, len + 1);
	free(line);
}

static void	ft_heredoc_loop(int write_fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = ft_read_heredoc_line();
		if (!line)
			break ;
		if (ft_check_delimiter(line, delimiter))
			break ;
		ft_write_heredoc_line(write_fd, line);
	}
}

int	ft_handle_heredoc(const char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	ft_heredoc_loop(pipefd[1], delimiter);
	close(pipefd[1]);
	return (pipefd[0]);
}
