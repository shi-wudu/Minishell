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

#include "minishell.h"

// Verifica se o comando corresponde a um builtin suportado pelo minishell.

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

// Executa um builtin com base no nome do comando (argv[0]).
// Atua como um dispatcher que encaminha para a função concreta.

int	exec_builtin(char **argv, char ***env, bool from_shell)
{
    if (ft_strcmp(argv[0], "echo") == 0)
        return (builtin_echo(argv));
    if (ft_strcmp(argv[0], "cd") == 0)
        return (builtin_cd(argv, env));
    if (ft_strcmp(argv[0], "pwd") == 0)
        return (builtin_pwd());
    if (ft_strcmp(argv[0], "export") == 0)
        return (builtin_export(argv, env));
    if (ft_strcmp(argv[0], "unset") == 0)
        return (builtin_unset(argv, env));
    if (ft_strcmp(argv[0], "env") == 0)
        return (builtin_env(*env));
    if (ft_strcmp(argv[0], "exit") == 0)
        return (builtin_exit(argv, from_shell));
    return (0);
}
