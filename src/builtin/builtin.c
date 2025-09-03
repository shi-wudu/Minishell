/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student42.lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:08 by marleand          #+#    #+#             */
/*   Updated: 2025/09/03 18:57:11 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") ||
			!ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "pwd") ||
			!ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "unset") ||
			!ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "exit"));
}

int	exec_builtin(char **argv, char **env)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	else if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, env));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, env));
	else if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, env));
	else if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(env));
	else if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	return (1);
}

int	builtin_echo(char **argv)  
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	if (argv[1] && argv[1][0] == '-' && echo_nnn_hander(argv[1]))
	{
		flag = 0;
		i = 2;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (flag)
		printf("\n");
	return (0);
}

