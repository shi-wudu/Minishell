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


int echo_nnn_handler(char *str)
{
	if (!str || str[0] != '-')
		return (0);

    str++;

	if (!*str)  // Just "-" with nothing after
		return (0);
    
    while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
    
	return (1);
}

int	builtin_echo(char **argv)  
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	if (argv[1] && argv[1][0] == '-' && echo_nnn_handler(argv[1]))
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

int builtin_cd(char **argv, char **env)
{
	char *path;
	if (!argv[1])
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell> cd: HOME not set", 2);
			return (1);
		}
	}
	else
	{
		path = argv[1];
	}

	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell> cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 1);
		perror(NULL);
		return (1);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char buffer[4096];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("minishell > pwd");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}