/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:30:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/17 20:20:10 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_generate_prompt(char **envp)
{
	char	*dir_path;
	char	*temp;
	char	*prompt;

	dir_path = ft_get_directory_path(envp);
	if (!dir_path)
		return (ft_strdup("minishell> "));
	temp = ft_strjoin(PROMPT_PREFIX, dir_path);
	free(dir_path);
	if (!temp)
		return (ft_strdup("minishell> "));
	prompt = ft_strjoin(temp, PROMPT_SUFFIX);
	free(temp);
	if (!prompt)
		return (ft_strdup("minishell> "));
	return (prompt);
}
