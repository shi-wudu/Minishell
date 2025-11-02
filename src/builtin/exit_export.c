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

static int is_valid_number(char *str)
{
	int i;
	
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

int builtin_exit(char **argv)
{
	int exit_code;
	printf("exit\n");
	if (!argv[1])
		exit(0);
	
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}

	if (!is_valid_number(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	
	exit_code = ft_atoi(argv[1]);
	exit(exit_code % 256);
}
int builtin_unset(char **argv, char **env)
{
	(void)argv;
	(void)env;
	return (0);
}