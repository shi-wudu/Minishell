/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-02 19:15:39 by user              #+#    #+#             */
/*   Updated: 2025-11-02 19:15:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verifica se uma string representa um número inteiro válido,
// permitindo um sinal opcional (+ ou -).

static int	is_valid_number(char *str)
{
	int	i;

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

// Verifica se uma string é um identificador válido de variável de ambiente.

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Implementação do builtin exit.
// Encerra o shell quando executado no processo pai.
// Valida argumentos numéricos, trata erros e calcula o exit status
// de acordo com as regras do bash (exit_code % 256).

int	builtin_exit(char **argv, bool from_shell)
{
	long	exit_code;

	if (from_shell)
		ft_putendl_fd("exit", 1);
	if (!argv[1])
		exit(0);
	if (!is_valid_number(argv[1]))
	{
		if (from_shell)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
		exit(255);
	}
	if (argv[2])
	{
		if (from_shell)
			ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	exit(exit_code % 256);
}

// Implementação do builtin export.
// Lista o ambiente quando chamado sem argumentos.
// Caso contrário, valida identificadores e adiciona ou atualiza
// variáveis de ambiente.

int	builtin_export(char **argv, char ***env)
{
	int	i;
	int	env_count;

	if (!argv[1])
		return (builtin_env(*env));
	env_count = 0;
	while ((*env)[env_count])
		env_count++;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
		if (ft_strchr(argv[i], '='))
			if (!update_or_add_var(env, argv[i], &env_count))
				return (1);
		i++;
	}
	return (0);
}
