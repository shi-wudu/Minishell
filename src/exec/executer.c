/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 16:08:39 by user              #+#    #+#             */
/*   Updated: 2025-11-30 16:08:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	execute_external(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("minishell: fork failed", 2);
		cmd->exit_status = 1;
		return ;
	}
	if (pid == 0)
		execute_child(cmd, -1, -1, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			cmd->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd->exit_status = 128 + WTERMSIG(status);
	}
}

void	execute_commands(t_cmd *cmd, char **envp)
{
	t_cmd	*current;

	if (!cmd)
		return ;
	current = cmd;
	while (current)
	{
		if (is_builtin(current->command))
			current->exit_status = exec_builtin(current->args, &envp);
		else
			execute_external(current, envp);
		current = current->next;
	}
}