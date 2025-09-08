/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/05 19:02:12 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <structs.h>

/**
 * is_valid_export_identifier - Verifica se identificador é válido para export
 */
static int	is_valid_export_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (0);
	return (1);
}

/**
 * find_env_variable - Procura variável de ambiente pelo nome
 */
static t_env_var	*find_env_variable(t_list *envp, const char *var_name)
{
	t_list	*current;
	t_env_var	*env_var;
	size_t	name_len;

	name_len = ft_strlen(var_name);
	current = envp;
	
	while (current)
	{
		env_var = (t_env_var *)current->content;
		if (ft_strncmp(env_var->value, var_name, name_len) == 0 &&
			env_var->value[name_len] == '=')
			return (env_var);
		current = current->next;
	}
	return (NULL);
}

/**
 * create_env_variable - Cria uma nova variável de ambiente
 */
static int	create_env_variable(t_shell *shell_data, const char *var_name, 
								const char *var_value)
{
	t_env_var	*new_var;
	char	*full_name;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (1);
	
	full_name = ft_strjoin(var_name, "=");
	if (!full_name)
	{
		free(new_var);
		return (1);
	}
	
	new_var->value = full_name;
	new_var->content = var_value ? ft_strdup(var_value) : ft_strdup("");
	new_var->is_export = true;
	new_var->printed = false;
	
	if (!new_var->content)
	{
		free(new_var->value);
		free(new_var);
		return (1);
	}
	
	ft_lstadd_back(&shell_data->envp, ft_lstnew(new_var));
	return (0);
}

/**
 * update_env_variable - Atualiza variável existente ou cria nova
 */
int	update_env_variable(t_shell *shell_data, const char *var_name,
								const char *var_value)
{
	t_env_var	*existing_var;

	existing_var = find_env_variable(shell_data->envp, var_name);
	
	if (existing_var)
	{
		free(existing_var->content);
		existing_var->content = ft_strdup(var_value);
		existing_var->is_export = true;
		return (existing_var->content ? 0 : 1);
	}
	else
	{
		return (create_env_variable(shell_data, var_name, var_value));
	}
}

/**
 * handle_export_append - Trata export com append (VAR+=value)
 */
static int	handle_export_append(t_shell *shell_data, const char *var_name,
								const char *append_value)
{
	t_env_var	*existing_var;
	char	*new_content;

	existing_var = find_env_variable(shell_data->envp, var_name);
	
	if (existing_var)
	{
		new_content = ft_strjoin(existing_var->content, append_value);
		if (!new_content)
			return (1);
		free(existing_var->content);
		existing_var->content = new_content;
		existing_var->is_export = true;
	}
	else
	{
		return (create_env_variable(shell_data, var_name, append_value));
	}
	return (0);
}

/**
 * print_export_variables - Imprime todas as variáveis de export
 */
static void	print_export_variables(t_list *envp)
{
	t_list	*current;
	t_env_var	*env_var;

	current = envp;
	while (current)
	{
		env_var = (t_env_var *)current->content;
		env_var->printed = false;
		current = current->next;
	}

	current = envp;
	while (current)
	{
		env_var = (t_env_var *)current->content;
		if (env_var->is_export && !env_var->printed)
		{
			printf("declare -x %s", env_var->value);
			if (env_var->content && ft_strlen(env_var->content) > 0)
				printf("\"%s\"", env_var->content);
			printf("\n");
			env_var->printed = true;
		}
		current = current->next;
	}
}

/**
 * export_variable - Implementa o comando export para uma variável
 */
int	export_variable(t_shell *shell_data, const char *arg_str)
{
	char	*equals_pos;
	char	*plus_pos;
	char	*var_name;
	char	*var_value;
	int		result;

	if (!is_valid_export_identifier(arg_str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)arg_str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}

	equals_pos = ft_strchr(arg_str, '=');
	plus_pos = ft_strchr(arg_str, '+');

	if (!equals_pos)
	{
		t_env_var *existing_var = find_env_variable(shell_data->envp, arg_str);
		if (existing_var)
			existing_var->is_export = true;
		else
			return (create_env_variable(shell_data, arg_str, NULL));
		return (0);
	}

	if (plus_pos && plus_pos + 1 == equals_pos)
	{
		var_name = ft_substr(arg_str, 0, plus_pos - arg_str);
		var_value = equals_pos + 1;
		result = handle_export_append(shell_data, var_name, var_value);
	}
	else
	{
		var_name = ft_substr(arg_str, 0, equals_pos - arg_str);
		var_value = equals_pos + 1;
		result = update_env_variable(shell_data, var_name, var_value);
	}

	free(var_name);
	return (result);
}

/**
 * builtin_export - Implementa o comando export
 */
int	builtin_export(t_shell *shell_data, char **arguments)
{
	int	i;
	int	exit_status;
	int	result;

	exit_status = 0;

	if (!arguments[1])
	{
		print_export_variables(shell_data->envp);
		return (0);
	}

	i = 1;
	while (arguments[i])
	{
		result = export_variable(shell_data, arguments[i]);
		if (result != 0)
			exit_status = 1;
		i++;
	}

	return (exit_status);
}

/* ************************************************************************** */
/*                                  UNSET                                    */
/* ************************************************************************** */

/**
 * is_valid_unset_identifier - Verifica se identificador é válido para unset
 */
static int	is_valid_unset_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * free_env_node - Libera memória de um nó de variável de ambiente
 */
static void	free_env_node(t_env_var *env_node)
{
	if (env_node)
	{
		if (env_node->value)
			free(env_node->value);
		if (env_node->content)
			free(env_node->content);
		free(env_node);
	}
}

/**
 * unset_variable - Remove uma variável de ambiente
 */
int	unset_variable(t_shell *shell_data, const char *var_name)
{
	t_list	*current;
	t_list	*prev;
	t_env_var	*env_var;
	size_t	name_len;

	if (!is_valid_unset_identifier(var_name))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd((char *)var_name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}

	name_len = ft_strlen(var_name);
	current = shell_data->envp;
	prev = NULL;

	while (current)
	{
		env_var = (t_env_var *)current->content;
		if (ft_strncmp(env_var->value, var_name, name_len) == 0 &&
			env_var->value[name_len] == '=')
		{
			if (prev)
				prev->next = current->next;
			else
				shell_data->envp = current->next;
			
			free_env_node(env_var);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * builtin_unset - Implementa o comando unset
 */
int	builtin_unset(t_shell *shell_data, char **arguments)
{
	int	i;
	int	exit_status;
	int	result;

	if (!arguments[1])
		return (0);

	exit_status = 0;
	i = 1;

	while (arguments[i])
	{
		result = unset_variable(shell_data, arguments[i]);
		if (result != 0)
			exit_status = 1;
		i++;
	}

	return (exit_status);
}

/* ************************************************************************** */
/*                                  EXIT                                     */
/* ************************************************************************** */

/**
 * ft_atoll - Converte string para long long
 */
static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	
	while (str[i] && ft_isspace(str[i]))
		i++;
	
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return (result * sign);
}

/**
 * is_numeric_argument - Verifica se string é um número válido
 */
static int	is_numeric_argument(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;

	if (!str[i])
		return (0);

	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}

	return (1);
}

/**
 * cleanup_and_exit - Libera recursos e faz exit
 */
static void	cleanup_and_exit(t_shell *shell_data, int exit_code)
{
	if (shell_data->envp)
		free_env_list(shell_data->envp);
	
	if (shell_data->input)
		free(shell_data->input);
	if (shell_data->trim_input)
		free(shell_data->trim_input);
	if (shell_data->cmd_path)
		free(shell_data->cmd_path);
	if (shell_data->cwd)
		free(shell_data->cwd);

	exit((unsigned char)exit_code);
}

/**
 * builtin_exit - Implementa o comando exit
 */
int	builtin_exit(t_shell *shell_data, char **arguments)
{
	long long	exit_code;

	ft_putendl_fd("exit", 2);

	if (!arguments[1])
	{
		cleanup_and_exit(shell_data, 0);
	}

	if (!is_numeric_argument(arguments[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arguments[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_and_exit(shell_data, 2);
	}

	if (arguments[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}

	exit_code = ft_atoll(arguments[1]);
	cleanup_and_exit(shell_data, (int)exit_code);

	return (0);
}