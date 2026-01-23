/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student42.lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:08 by marleand          #+#    #+#             */
/*   Updated: 2025/09/03 18:57:11 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cria um filho com fork e chama execute_child no filho
// child: execute_child cuida de sinais, redirs e exec/builtin e exit
// se execute_child voltar, garantimos sair
static pid_t	spawn_child(t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("minishell: fork failed", 2);
		return (-1);
	}
	if (pid == 0)
	{
		execute_child(cmd, -1, -1, data);
		cleanup_and_exit_child(data, 127);
	}
	return (pid);
}

// espera um pid com retry em EINTR e decodifica o estado de saida
static int	wait_for_child(pid_t pid)
{
	int		status;
	pid_t	w;
	int		sig;

	status = 0;
	w = waitpid(pid, &status, 0);
	while (w == -1 && errno == EINTR)
		w = waitpid(pid, &status, 0);
	if (w == -1)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + sig);
	}
	return (1);
}

static void	update_exit_status(t_cmd *cmd, int code, t_data *data)
{
	cmd->exit_status = code;
	if (data)
		data->last_exit_status = code;
}

static void	execute_one_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		code;

	pid = spawn_child(cmd, data);
	if (pid == -1)
	{
		update_exit_status(cmd, 1, data);
		return ;
	}
	code = wait_for_child(pid);
	if (code == -1)
		code = 1;
	update_exit_status(cmd, code, data);
}

// cria filhos para cada comando (sem pipes), espera e actualiza exit_status
void	execute_main(t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		execute_one_cmd(cmd, data);
		cmd = cmd->next;
	}
}
