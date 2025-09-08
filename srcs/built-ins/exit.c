/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:03:34 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/08 18:35:57 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_limits(char *str, long long num)
{
	if (num > LLONG_MAX || num < LLONG_MIN)
		return (0);
	if (num == LLONG_MAX && ft_strcmp(str, "9223372036854775807"))
		return (0);
	if (num == LLONG_MIN && ft_strcmp(str, "-9223372036854775808"))
		return (0);
	return (1);
}

int	is_numeric(char *str)
{
	int			i;
	int			flag;
	long long	num;

	i = 0;
	flag = 0;
	if (!str)
		return (0);
	num = ft_atoll(str);
	if (!check_limits(str, num))
		return (0);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str[i] == '-')
		return (0);
	while (str[i])
	{
		if (str[i] && ft_isdigit(str[i]))
			flag = 1;
		else
			return (0);
		i++;
	}
	return (flag);
}

void	exit_error(t_shell *shell, char **arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_env_list(shell->envp);
	free_shell(shell);
	exit(2);
}

static void	numeric_exit(t_shell *shell, char **args)
{
	long long	status;

	status = ft_atoll(args[1]);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ; // Não sai, apenas retorna erro
	}
	free_env_list(shell->envp);
	free_shell(shell);
	exit((unsigned char)status);
}

void	ft_exit(t_shell *shell, t_exec *exec_node)
{
	char	**args;

	args = exec_node->argv;
	
	// Se não há argumentos, sai com código 0
	if (!args || !args[1])
	{
		free_env_list(shell->envp);
		free_shell(shell);
		exit(0);
	}
	
	// Se o argumento é numérico, usa como código de saída
	if (is_numeric(args[1]))
	{
		numeric_exit(shell, args);
		return;
	}
	
	// Se não é numérico, erro
	exit_error(shell, args);
}

void	exit_args(t_shell *shell, char **args, int argc)
{
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	if (argc == 2)
	{
		if (is_numeric(args[1]))
		{
			long long status = ft_atoll(args[1]);
			free_env_list(shell->envp);
			free_shell(shell);
			exit((unsigned char)status);
		}
		else
		{
			exit_error(shell, args);
		}
	}
	else
	{
		free_env_list(shell->envp);
		free_shell(shell);
		exit(0);
	}
}
