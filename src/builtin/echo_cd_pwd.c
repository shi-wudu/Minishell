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

#include "../../minishell.h"


static int echo_nnn_handler(char *str)
{
	if (*str == '-')
		str++;
    else
        return (0);
	while (*str)
	{
		if (*str == 'n')
			str++;
		else
			return (0);
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

int builtin_cd(char **argv, )

int main(int ac, char **argv)
{
    builtin_echo(argv);
    return 0;
}