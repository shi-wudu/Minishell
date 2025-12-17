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


// se for necessario configurar stdin/stdout vindos de pipes, faz dup2 e fecha fds
static void	child_setup_fds(int in_fd, int out_fd)
{
    if (in_fd != -1)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != -1)
    {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
}

// no filho: repoe sinais para o comportamento por omissao e aplica redirecoes
// se apply_redirections falhar termina o filho imediatamente
static void	child_prepare_and_redir(t_cmd *cmd, t_data *data)
{
    // repoe sinais para o comportamento por omissao nos filhos
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    // aplica redirecoes (vai dup2 e fechar fds). apply_redirections espera t_cmd*
    if (apply_redirections(cmd, data->envp, data->last_exit_status) != 0)
        exit(1);
}

// executa um builtin no contexto do filho (porque pode haver redirs/pipes)
static void	child_exec_builtin(t_cmd *cmd, t_data *data)
{
    int	code;

    code = exec_builtin(cmd->args, &data->envp, false);
    exit(code);
}

// executa binario externo: resolve path, execve, e em erro escolhe 126/127
static void	child_exec_external(t_cmd *cmd, t_data *data)
{
    char	*path;

    ft_putstr_fd("debug: child_exec_external cmd=", 2);
    if (cmd->command)
        ft_putendl_fd(cmd->command, 2);
    else
        ft_putendl_fd("(null)", 2);

    path = resolve_path(cmd->command, data->envp);
    if (!path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->command, 2);
        ft_putendl_fd(": command not found", 2);
        exit(127);
    }
    execve(path, cmd->args, data->envp);
    // se execve retorna ha um erro; determinar codigo
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
        exit(126);
    exit(127);
}

// funcao chamada no filho: configura fds, redirs e executa builtin ou externo
// o filho deve terminar com exit e nao voltar ao pai
void	execute_child(t_cmd *cmd, int in_fd, int out_fd, t_data *data)
{
    child_setup_fds(in_fd, out_fd);
    child_prepare_and_redir(cmd, data);
    if (is_builtin(cmd->command))
        child_exec_builtin(cmd, data);
    else
        child_exec_external(cmd, data);
    // seguranca: em caso inesperado
    exit(127);
}

// se for um builtin isolado sem redirecoes nem pipes pode executar no pai
static int	is_parent_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->command)
        return (0);
    if (!is_builtin(cmd->command))
        return (0);
    if (cmd->io.infile || cmd->io.outfile || cmd->io.heredoc)
        return (0);
    if (cmd->pipe_output)
        return (0);
    return (1);
}

// cria um filho com fork e chama execute_child no filho
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
        // child: execute_child cuida de sinais, redirs e exec/builtin e exit
        execute_child(cmd, -1, -1, data);
        // se execute_child voltar, garantimos sair
        exit(127);
    }
    return (pid);
}

// espera um pid com retry em EINTR e decodifica o estado de saida
static int	wait_for_child(pid_t pid)
{
    int		status;
    pid_t	w;

    status = 0;
    while ((w = waitpid(pid, &status, 0)) == -1 && errno == EINTR)
        ;
    if (w == -1)
        return (-1);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (1);
}

// cria filhos para cada comando (sem pipes), espera e actualiza exit_status
static void	execute_main(t_cmd *cmd, t_data *data)
{
    t_cmd	*current;
    int		last_status;
    pid_t	pid;
    int		exit_code;

    if (!cmd)
        return ;
    current = cmd;
    last_status = 0;
    while (current)
    {
        pid = spawn_child(current, data);
        if (pid == -1)
        {
            current->exit_status = 1;
            last_status = 1;
            if (data)
                data->last_exit_status = last_status;
            current = current->next;
            continue ;
        }
        exit_code = wait_for_child(pid);
        if (exit_code == -1)
            current->exit_status = 1;
        else
            current->exit_status = exit_code;
        last_status = current->exit_status;
        if (data)
            data->last_exit_status = last_status;
        current = current->next;
    }
}

// entrada principal: delega pipelines, executa builtin no pai quando seguro
// senao cria filhos para cada comando e actualiza data->last_exit_status
void	execute_commands(t_cmd *cmd, t_data *data)
{
    t_cmd	*current;
    int		last_status;

    if (!cmd)
        return ;
    ft_putstr_fd("debug: execute_commands cmd=", 2);
    if (cmd->command)
        ft_putendl_fd(cmd->command, 2);
    else
        ft_putendl_fd("(null)", 2);
    if (data && data->envp && data->envp[0])
    {
        ft_putstr_fd("debug: envp[0]=", 2);
        ft_putendl_fd(data->envp[0], 2);
    }
    // se houver pipeline, delega para o executor das pipes
    if (cmd->next)
    {
        execute_commands_piped(cmd, data);
        return ;
    }
    current = cmd;
    // se for builtin isolado sem redirs executa no processo pai
    if (is_parent_builtin(current))
    {
        last_status = exec_builtin(current->args, &data->envp, true);
        current->exit_status = last_status;
        data->last_exit_status = last_status;
        return ;
    }
    // senao spawn+wait para cada comando (child faz redirs/exec)
    execute_main(current, data);
}