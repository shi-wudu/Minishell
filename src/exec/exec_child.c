/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student42.lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:08 by marleand          #+#    #+#             */
/*   Updated: 2025/09/03 18:57:11 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// se for necessario configurar stdin/stdout vindos de pipes,
//	faz dup2 e fecha fds
static void	child_setup_fds(int in_fd, int out_fd)
{
	if (in_fd != -1 && in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1 && out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

// no filho: repoe sinais para o comportamento por omissao e aplica redirecoes
// se apply_redirections falhar termina o filho imediatamente
// aplica redirecoes (vai dup2 e fechar fds). apply_redirections espera t_cmd*
static void	child_prepare_and_redir(t_cmd *cmd, t_data *data)
{
	int	ret;

	ret = apply_redirections(cmd);
	if (ret != 0)
		cleanup_and_exit_child(data, 1);
}

// executa um builtin no contexto do filho (porque pode haver redirs/pipes)
static void	child_exec_builtin(t_cmd *cmd, t_data *data)
{
	int	code;

	code = exec_builtin(cmd->args, &data->envp, false);
	cleanup_and_exit_child(data, code);
}

// executa binario externo: resolve path, execve, e em erro escolhe 126/127
/*ft_putstr_fd("debug: child_exec_external cmd=", 2);
	if (cmd->command)
		ft_putendl_fd(cmd->command, 2);
	else
		ft_putendl_fd("(null)", 2);
	*/
// se execve retorna ha um erro; determinar codigo
static void	child_exec_external(t_cmd *cmd, t_data *data)
{
	char	*path;

	path = resolve_path(cmd->command, data->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->command, 2);
		ft_putendl_fd(": command not found", 2);
		cleanup_and_exit_child(data, 127);
	}
	execve(path, cmd->args, data->envp);
	if (errno == EACCES)
		ft_putendl_fd("minishell: permission denied", 2);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->command, 2);
		ft_putendl_fd(": exec failed", 2);
	}
	free(path);
	if (errno == EACCES)
		cleanup_and_exit_child(data, 126);
	cleanup_and_exit_child(data, 127);
}

// funcao chamada no filho: configura fds, redirs e executa builtin ou externo
// o filho deve terminar com exit e nao voltar ao pai
void	execute_child(t_cmd *cmd, int in_fd, int out_fd, t_data *data)
{
	setup_signals_child();
	child_setup_fds(in_fd, out_fd);
	child_prepare_and_redir(cmd, data);
	if (is_builtin(cmd->command))
		child_exec_builtin(cmd, data);
	else
		child_exec_external(cmd, data);
	cleanup_and_exit_child(data, 127);
}
