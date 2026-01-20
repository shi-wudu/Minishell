/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:08:39 by user              #+#    #+#             */
/*   Updated: 2026/01/20 21:38:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// se for um builtin isolado sem redirecoes nem pipes pode executar no pai
static int	is_parent_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->command)
		return (0);
	if (!is_builtin(cmd->command))
		return (0);
	if (cmd->io.infile || cmd->io.outfile || cmd->heredoc_count > 0)
		return (0);
	if (cmd->pipe_output)
		return (0);
	return (1);
}

static int	exec_parent_builtin(t_cmd *cmd, t_data *data)
{
	int	status;

	if (ft_strcmp(cmd->command, "exit") == 0)
	{
		status = builtin_exit(cmd->args, true);
		cleanup_iteration(data);
		free_all(data);
		exit(status);
	}
	status = exec_builtin(cmd->args, &data->envp, true);
	cmd->exit_status = status;
	data->last_exit_status = status;
	return (1);
}

// entrada principal: delega pipelines, executa builtin no pai quando seguro
// senao cria filhos para cada comando e actualiza data->last_exit_status
/*ft_putstr_fd("debug: execute_commands cmd=", 2);
if (cmd->command)
	ft_putendl_fd(cmd->command, 2);
else
	ft_putendl_fd("(null)", 2);
if (data && data->envp && data->envp[0])
{
	ft_putstr_fd("debug: envp[0]=", 2);
	ft_putendl_fd(data->envp[0], 2);
}*/

// se houver pipeline, delega para o executor das pipes
// se for builtin isolado sem redirs executa no processo pai
// senao spawn+wait para cada comando (child faz redirs/exec)

int	execute_commands(t_cmd *cmd, t_data *data)
{
	t_cmd	*current;
	int		ret;

	if (!cmd)
		return (0);
	ret = prepare_heredocs(cmd, data);
	if (ret == 130)
		return (130);
	if (cmd->next)
	{
		execute_commands_piped(cmd, data);
		return (1);
	}
	current = cmd;
	if (is_parent_builtin(current))
		return (exec_parent_builtin(cmd, data));
	setup_signals_parent_exec();
	execute_main(current, data);
	setup_signals_interactive();
	return (1);
}
