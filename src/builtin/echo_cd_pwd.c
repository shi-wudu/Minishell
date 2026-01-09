/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student42.lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:56:16 by marleand          #+#    #+#             */
/*   Updated: 2025/09/03 19:25:50 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verifica se uma string corresponde ao formato válido de opções -n
// para o builtin echo (ex: -n, -nn, -nnnn).
// Retorna 1 se for válida, 0 caso contrário.

int	echo_nnn_handler(char *str)
{
	if (!str || str[0] != '-')
		return (0);
	str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

// Implementação do builtin echo.
// Imprime os argumentos separados por espaços e adiciona uma newline


int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (argv[i] && echo_nnn_handler(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

// Implementação do builtin cd.
// Altera o diretório de trabalho do processo atual

int	builtin_cd(char **argv, char **env)
{
	char	cwd[PATH_MAX];
	char	*path;

	path = argv[1];
	if (!path)
		path = get_env_value(env, "HOME");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd("minishell: pwd: getcwd failed", 2);
		return (1);
	}
	return (0);
}

// Implementação do builtin pwd.
// Obtém e imprime o diretório de trabalho atual.

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd("minishell: pwd: getcwd failed", 2);
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	return (0);
}
