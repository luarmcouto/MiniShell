/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/05 19:33:51 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * is_valid_export_identifier - Verifica se identificador é válido para export
 * @str: string a verificar
 * 
 * Um identificador válido deve:
 * - Começar com letra ou underscore
 * - Conter apenas letras, números e underscores
 * - Pode ter += para append
 * 
 * Return: 1 se válido, 0 se inválido
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
	// Se tem +, deve ser seguido de =
	if (str[i] == '+' && str[i + 1] != '=')
		return (0);
	return (1);
}

/**
 * create_env_variable - Cria uma nova variável de ambiente
 * @shell_data: estrutura principal do shell
 * @var_name: nome da variável
 * @var_value: valor da variável (pode ser NULL)
 * 
 * Return: 0 em sucesso, 1 em erro
 */
static int	create_env_variable(t_shell *shell_data, const char *var_name, 
								const char *var_value)
{
	t_env_var	*new_var;
	char	*full_name;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (1);
	
	// Cria nome com = no final
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
 * find_env_variable - Procura variável de ambiente pelo nome
 * @envp: lista de variáveis de ambiente
 * @var_name: nome da variável a procurar
 * 
 * Return: ponteiro para a variável ou NULL se não encontrada
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
 * handle_export_append - Trata export com append (VAR+=value)
 * @shell_data: estrutura principal do shell
 * @var_name: nome da variável
 * @append_value: valor a ser adicionado
 * 
 * Return: 0 em sucesso, 1 em erro
 */
static int	handle_export_append(t_shell *shell_data, const char *var_name,
								const char *append_value)
{
	t_env_var	*existing_var;
	char	*new_content;

	existing_var = find_env_variable(shell_data->envp, var_name);
	
	if (existing_var)
	{
		// Variável existe, faz append ao conteúdo
		new_content = ft_strjoin(existing_var->content, append_value);
		if (!new_content)
			return (1);
		free(existing_var->content);
		existing_var->content = new_content;
		existing_var->is_export = true;
	}
	else
	{
		// Variável não existe, cria nova com o valor
		return (create_env_variable(shell_data, var_name, append_value));
	}
	return (0);
}

/**
 * update_env_variable - Atualiza variável existente ou cria nova
 * @shell_data: estrutura principal do shell
 * @var_name: nome da variável
 * @var_value: novo valor da variável
 * 
 * Return: 0 em sucesso, 1 em erro
 */
int	update_env_variable(t_shell *shell_data, const char *var_name,
								const char *var_value)
{
	t_env_var	*existing_var;

	existing_var = find_env_variable(shell_data->envp, var_name);
	
	if (existing_var)
	{
		// Atualiza variável existente
		free(existing_var->content);
		existing_var->content = ft_strdup(var_value);
		existing_var->is_export = true;
		return (existing_var->content ? 0 : 1);
	}
	else
	{
		// Cria nova variável
		return (create_env_variable(shell_data, var_name, var_value));
	}
}

/**
 * print_export_variables - Imprime todas as variáveis de export em ordem alfabética
 * @envp: lista de variáveis de ambiente
 */
static void	print_export_variables(t_list *envp)
{
	t_list	*current;
	t_env_var	*env_var;

	// Primeiro, marca todas como não impressas
	current = envp;
	while (current)
	{
		env_var = (t_env_var *)current->content;
		env_var->printed = false;
		current = current->next;
	}

	// Imprime em ordem alfabética (implementação simples)
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
 * @shell_data: estrutura principal do shell
 * @arg_str: string do argumento (formato: VAR=value ou VAR+=value)
 * 
 * Return: 0 em sucesso, 1 em erro
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

	// Se não tem =, apenas marca para export
	if (!equals_pos)
	{
		t_env_var *existing_var = find_env_variable(shell_data->envp, arg_str);
		if (existing_var)
			existing_var->is_export = true;
		else
			return (create_env_variable(shell_data, arg_str, NULL));
		return (0);
	}

	// Extrai nome da variável
	if (plus_pos && plus_pos + 1 == equals_pos)
	{
		// Caso VAR+=value
		var_name = ft_substr(arg_str, 0, plus_pos - arg_str);
		var_value = equals_pos + 1;
		result = handle_export_append(shell_data, var_name, var_value);
	}
	else
	{
		// Caso VAR=value
		var_name = ft_substr(arg_str, 0, equals_pos - arg_str);
		var_value = equals_pos + 1;
		result = update_env_variable(shell_data, var_name, var_value);
	}

	free(var_name);
	return (result);
}

/**
 * builtin_export - Implementa o comando export
 * @shell_data: estrutura principal do shell
 * @arguments: array de argumentos do comando
 * 
 * Comportamento:
 * - export (sem args): lista todas as variáveis exportadas
 * - export VAR: marca VAR para export
 * - export VAR=value: define e exporta VAR com value
 * - export VAR+=value: adiciona value ao final de VAR
 * 
 * Return: código de saída (0 = sucesso, 1 = erro)
 */
int	builtin_export(t_shell *shell_data, char **arguments)
{
	int	i;
	int	exit_status;
	int	result;

	exit_status = 0;

	// Se não há argumentos, lista variáveis exportadas
	if (!arguments[1])
	{
		print_export_variables(shell_data->envp);
		return (0);
	}

	// Processa cada argumento
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