/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:30:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/06 12:47:49 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <ctype.h>

static char	*ft_append_literal(char *result, char *argv, int start, int end)
{
	char	*temp;
	char	*old_str;

	if (end <= start)
		return (result);
	temp = ft_substr(argv, start, end - start);
	old_str = result;
	result = ft_strjoin(old_str, temp);
	free(old_str);
	free(temp);
	return (result);
}

char	*ft_expand_exit_status(char *result, t_data *data)
{
	char	*temp;
	char	*old_str;

	temp = ft_itoa(data->last_exit_status);
	if (!temp)
		return (NULL);
	old_str = result;
	result = ft_strjoin(old_str, temp);
	free(old_str);
	free(temp);
	return (result);
}

char	*ft_expand_env_var(char *result, char *argv, int *j, t_data *data)
{
	int		start;
	char	*env_name;
	char	*env_value;
	char	*old_str;

	start = *j;
	if (argv[*j] >= '0' && argv[*j] <= '9')
	{
		(*j)++;
		return (result);
	}
	while (argv[*j] && (isalnum(argv[*j]) || argv[*j] == '_'))
		(*j)++;
	if (*j > start)
	{
		env_name = ft_substr(argv, start, *j - start);
		env_value = ft_getenv(env_name, data->envp);
		if (env_value)
		{
			old_str = result;
			result = ft_strjoin(old_str, env_value);
			free(old_str);
		}
		free(env_name);
		return (result);
	}
	old_str = result;
	result = ft_strjoin(old_str, "$");
	free(old_str);
	return (result);
}

static char	*ft_expand_string(char *argv, t_data *data)
{
	char	*result;
	int		j;
	int		start;

	if (argv[0] == '\'' && argv[ft_strlen(argv) - 1] == '\'')
		return (ft_strdup(argv));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	j = 0;
	while (argv[j])
	{
		start = j;
		while (argv[j] && argv[j] != '$')
			j++;
		result = ft_append_literal(result, argv, start, j);
		if (!result)
			return (NULL);
		result = ft_process_expansion(result, argv, &j, data);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	**ft_handle_env_expansion(char **argv, t_data *data)
{
	int		i;
	char	**new_argv;

	if (!argv || !data || !data->envp)
		return (argv);
	new_argv = malloc(sizeof(char *) * (data->argc + 1));
	if (!new_argv)
		return (argv);
	i = 0;
	while (argv[i])
	{
		new_argv[i] = ft_expand_string(argv[i], data);
		if (!new_argv[i])
		{
			while (--i >= 0)
				free(new_argv[i]);
			free(new_argv);
			return (argv);
		}
		i++;
	}
	new_argv[i] = NULL;
	return (new_argv);
}
