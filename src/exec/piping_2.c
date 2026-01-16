/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:50:12 by user              #+#    #+#             */
/*   Updated: 2026/01/16 13:05:49 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_pipe_fds(t_pipe_ctx *ctx, int idx, int *in_fd, int *out_fd)
{
	*in_fd = -1;
	*out_fd = -1;
	if (idx > 0)
		*in_fd = ctx->pipes[(idx - 1) * 2];
	if (idx < ctx->n - 1)
		*out_fd = ctx->pipes[idx * 2 + 1];
}

static void	child_close_unused_pipes(t_pipe_ctx *ctx, int idx)
{
	int	j;

	j = 0;
	while (j < ctx->n - 1)
	{
		if (j != idx - 1)
			close(ctx->pipes[j * 2]);
		if (j != idx)
			close(ctx->pipes[j * 2 + 1]);
		j++;
	}
}

// cria um filho para o indice idx do pipeline
// o filho fica com in_fd/out_fd (read/write ends) e fecha os outros fds
// retorna pid do filho no parent, -1 em erro
// child: fechar fds que nao sao o in_fd/out_fd
// execute_child vai dup2, aplicar redirs e exec/exit

pid_t	spawn_pipeline_child(t_pipe_ctx *ctx, int idx)
{
	pid_t	pid;
	int		in_fd;
	int		out_fd;

	get_pipe_fds(ctx, idx, &in_fd, &out_fd);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		child_close_unused_pipes(ctx, idx);
		execute_child(ctx->cmds[idx], in_fd, out_fd, ctx->data);
		exit(127);
	}
	return (pid);
}

void	ensure_standard_fds_open(void)
{
	int	fd;
	int	tmp;

	fd = 0;
	while (fd <= 2)
	{
		if (fcntl(fd, F_GETFD) == -1 && errno == EBADF)
		{
			tmp = open("/dev/null", O_RDWR);
			if (tmp != -1)
			{
				dup2(tmp, fd);
				if (tmp > 2)
					close(tmp);
			}
		}
		fd ++;
	}
}
