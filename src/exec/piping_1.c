/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:50:12 by user              #+#    #+#             */
/*   Updated: 2026/01/23 07:17:59 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cria (n - 1) pipes e devolve um array linear de fds (2*pairs)
// devolve NULL em erro
// fechar fds ja criados em caso de erro
static int	*create_pipes(int n)
{
	int	*pipes;
	int	i;

	if (n < 2)
		return (NULL);
	pipes = malloc(sizeof(int) * 2 * (n - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < n - 1)
	{
		if (pipe(&pipes[i * 2]) == -1)
		{
			while (--i >= 0)
			{
				close(pipes[i * 2]);
				close(pipes[i * 2 + 1]);
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

// spawn de todos os filhos do pipeline; devolve
// quantos filhos foram criados (0..n)
// em caso de erro devolve o numero criado ate ao
// momento (pids preenchidos de 0..created-1)
static int	spawn_all_children(t_pipe_ctx *ctx)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < ctx->n)
	{
		pid = spawn_pipeline_child(ctx, i);
		if (pid == -1)
			return (i);
		ctx->pids[i] = pid;
		i++;
	}
	return (ctx->n);
}

static int	handle_signaled_status(int status, int *printed_signal)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT)
	{
		if (!*printed_signal)
		{
			write(1, "\n", 1);
			*printed_signal = 1;
		}
	}
	else if (sig == SIGQUIT)
	{
		if (!*printed_signal)
		{
			write(2, "Quit (core dumped)\n", 19);
			*printed_signal = 1;
		}
	}
	return (128 + sig);
}

// espera count filhos e grava exit_status em cada comando
void	wait_and_collect(t_pipe_ctx *ctx, int count)
{
	int	i;
	int	status;
	int	printed_signal;

	i = 0;
	printed_signal = 0;
	while (i < count)
	{
		status = 0;
		if (waitpid(ctx->pids[i], &status, 0) == -1)
			ctx->cmds[i]->exit_status = 1;
		else if (WIFEXITED(status))
			ctx->cmds[i]->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ctx->cmds[i]->exit_status = handle_signaled_status(status,
					&printed_signal);
		i++;
	}
	if (count > 0)
		ctx->data->last_exit_status = ctx->cmds[count - 1]->exit_status;
}

// executor principal de pipelines: coordena criacao de pipes,
// fork e espera
// se nao houver comando retorna; se houver erros, limpa recursos
// antes de sair
// inicializa pids a 0 para evitar lixo em caminhos de erro
// spawn children: devolve quantos foram efectivamente criados
// parent fecha todos os fds de pipes assim que os filhos foram
// criados (ou tentou criar)
// erro no fork em algum ponto: matar e esperar apenas os spawnados
// esperar todos os filhos normalmente

void	execute_commands_piped(t_cmd *cmd, t_data *data)
{
	t_pipe_ctx	*ctx;
	int			spawned;

	if (!cmd)
		return ;
	ctx = malloc(sizeof(t_pipe_ctx));
	if (!ctx)
		return ;
	ensure_standard_fds_open();
	setup_signals_parent_exec();
	ctx->n = count_cmds(cmd);
	ctx->cmds = collect_cmds(cmd, ctx->n);
	ctx->pipes = create_pipes(ctx->n);
	ctx->pids = malloc(sizeof(pid_t) * ctx->n);
	ctx->data = data;
	data->pipe_ctx = ctx;
	spawned = spawn_all_children(ctx);
	close_all_pipes(ctx->pipes, ctx->n);
	free(ctx->pipes);
	pipeline_cleanup_and_wait(ctx, spawned);
	free(ctx);
	data->pipe_ctx = NULL;
	setup_signals_interactive();
}
