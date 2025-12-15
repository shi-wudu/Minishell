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
 
void	close_pipes(int *pipefd)
{
    if (pipefd)
    {
        if (pipefd[0] != -1)
            close(pipefd[0]);
        if (pipefd[1] != -1)
            close(pipefd[1]);
    }
}

void	close_all_fds(int *pipefd, int in_fd, int out_fd)
{
    close_pipes(pipefd);
    if (in_fd != STDIN_FILENO && in_fd != -1)
        close(in_fd);
    if (out_fd != STDOUT_FILENO && out_fd != -1)
        close(out_fd);
}

int	create_pipe(int *pipefd)
{
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    return (0);
}