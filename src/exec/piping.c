/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 17:50:12 by user              #+#    #+#             */
/*   Updated: 2025-11-30 17:50:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// cria (n - 1) pipes e devolve um array linear de fds (2*pairs)
// devolve NULL em erro
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
            // fechar fds ja criados em caso de erro
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

// cria um filho para o indice idx do pipeline
// o filho fica com in_fd/out_fd (read/write ends) e fecha os outros fds
// retorna pid do filho no parent, -1 em erro
static pid_t	spawn_pipeline_child(t_cmd *cmd, int *pipes, int idx, int n, t_data *data)
{
    pid_t	pid;
    int		in_fd;
    int		out_fd;
    int		j;

    in_fd = -1;
    out_fd = -1;
    if (idx > 0)
        in_fd = pipes[(idx - 1) * 2];
    if (idx < n - 1)
        out_fd = pipes[idx * 2 + 1];
    pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
        // child: fechar fds que nao sao o in_fd/out_fd
        j = 0;
        while (j < n - 1)
        {
            if ((idx - 1) != j)
                close(pipes[j * 2]);
            if (idx != j)
                close(pipes[j * 2 + 1]);
            j++;
        }
        // execute_child vai dup2, aplicar redirs e exec/exit
        execute_child(cmd, in_fd, out_fd, data);
        exit(127);
    }
    return (pid);
}

// spawn de todos os filhos do pipeline; devolve quantos filhos foram criados (0..n)
// em caso de erro devolve o numero criado ate ao momento (pids preenchidos de 0..created-1)
static int	spawn_all_children(t_cmd **cmds, int *pipes, pid_t *pids, int n, t_data *data)
{
    int	i;
    pid_t	p;

    i = 0;
    while (i < n)
    {
        p = spawn_pipeline_child(cmds[i], pipes, i, n, data);
        if (p == -1)
            return (i);
        pids[i] = p;
        i++;
    }
    return (n);
}

// espera count filhos e grava exit_status em cada comando
static void	wait_and_collect(pid_t *pids, t_cmd **cmds, int count, t_data *data)
{
    int	i;
    int	status;
    int	code;

    i = 0;
    while (i < count)
    {
        status = 0;
        if (waitpid(pids[i], &status, 0) == -1)
        {
            cmds[i]->exit_status = 1;
        }
        else if (WIFEXITED(status))
        {
            code = WEXITSTATUS(status);
            cmds[i]->exit_status = code;
        }
        else if (WIFSIGNALED(status))
            cmds[i]->exit_status = 128 + WTERMSIG(status);
        i++;
    }
    if (data && count > 0)
        data->last_exit_status = cmds[count - 1]->exit_status;
}

// executor principal de pipelines: coordena criacao de pipes, fork e espera
// se nao houver comando retorna; se houver erros, limpa recursos antes de sair
void	execute_commands_piped(t_cmd *cmd, t_data *data)
{
    int		n;
    t_cmd	**cmds;
    int		*pipes;
    pid_t	*pids;
    int		spawned;
    int		i;

    setup_signals_parent_exec();
    if (!cmd)
        return ;
    n = count_cmds(cmd);
    cmds = collect_cmds(cmd, n);
    if (!cmds)
        return ;
    pipes = create_pipes(n);
    pids = malloc(sizeof(pid_t) * n);
    if (!pids)
    {
        free(cmds);
        close_all_pipes(pipes, n);
        free(pipes);
        return ;
    }
    // inicializa pids a 0 para evitar lixo em caminhos de erro
    i = 0;
    while (i < n)
        pids[i++] = 0;
    // spawn children: devolve quantos foram efectivamente criados
    spawned = spawn_all_children(cmds, pipes, pids, n, data);
    // parent fecha todos os fds de pipes assim que os filhos foram criados (ou tentou criar)
    close_all_pipes(pipes, n);
    free(pipes);
    if (spawned != n)
    {
        // erro no fork em algum ponto: matar e esperar apenas os spawnados
        kill_children(pids, spawned);
        wait_and_collect(pids, cmds, spawned, data);
        free(pids);
        free(cmds);
        return ;
    }
    // esperar todos os filhos normalmente
    wait_and_collect(pids, cmds, n, data);
    setup_signals_interactive();
    free(pids);
    free(cmds);
}