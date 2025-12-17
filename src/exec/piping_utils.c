/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 17:53:14 by user              #+#    #+#             */
/*   Updated: 2025-11-30 17:53:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
    char	**temp;

    temp = args;
    if (!args)
        return ;
    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(args);
}
 
// conta quantos comandos ha na lista ligada
int	count_cmds(t_cmd *cmd)
{
    int	n;

    n = 0;
    while (cmd)
    {
        n++;
        cmd = cmd->next;
    }
    return (n);
}

// colecta os pointers para os comandos numa array (para indexacao)
t_cmd **collect_cmds(t_cmd *cmd, int n)
{
    t_cmd	**arr;
    int		i;

    arr = malloc(sizeof(t_cmd *) * n);
    if (!arr)
        return (NULL);
    i = 0;
    while (i < n && cmd)
    {
        arr[i++] = cmd;
        cmd = cmd->next;
    }
    return (arr);
}

// fecha todos os fds dos pipes criados
void	close_all_pipes(int *pipes, int n)
{
    int	i;

    if (!pipes || n < 2)
        return ;
    i = 0;
    while (i < n - 1)
    {
        close(pipes[i * 2]);
        close(pipes[i * 2 + 1]);
        i++;
    }
}

// envia SIGTERM para os filhos spawnados (usado em erro)
void	kill_children(pid_t *pids, int count)
{
    int	i;

    i = 0;
    while (i < count)
    {
        if (pids[i] > 0)
            kill(pids[i], SIGTERM);
        i++;
    }
}