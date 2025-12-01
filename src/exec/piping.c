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


static void	handle_child_process(t_cmd *cmd, int in_fd, int out_fd, char **envp)
{
    char	*path;

    if (apply_redirections(cmd) == -1)
        exit(1);
    
    if (in_fd != STDIN_FILENO)
    {
        if (dup2(in_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(in_fd);
    }
    
    if (out_fd != STDOUT_FILENO)
    {
        if (dup2(out_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(out_fd);
    }
    
    if (is_builtin(cmd->command))
        exit(exec_builtin(cmd->args, (char ***)&envp));
    
    path = resolve_path(cmd->command, envp);
    if (!path)
    {
        ft_putstr_fd("minishell: command not found: ", 2);
        ft_putendl_fd(cmd->command, 2);
        exit(127);
    }
    
    if (execve(path, cmd->args, envp) == -1)
    {
        perror("execve");
        free(path);
        exit(1);
    }
}

void	execute_child(t_cmd *cmd, int in_fd, int out_fd, char **envp)
{
    handle_child_process(cmd, in_fd, out_fd, envp);
}

static void	wait_for_children(t_cmd *cmd)
{
    int		status;
    pid_t	pid;
    t_cmd	*current;

    current = cmd;
    while (current)
    {
        if (current->exit_status != 0)
        {
            pid = waitpid(current->exit_status, &status, 0);
            if (pid == -1)
                break ;
            
            if (WIFEXITED(status))
                current->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                current->exit_status = 128 + WTERMSIG(status);
            else
                current->exit_status = 1;
        }
        current = current->next;
    }
}

void	execute_commands_piped(t_cmd *cmd, char **envp)
{
    t_cmd	*current;
    int		pipefd[2];
    int		in_fd;
    int		out_fd;
    pid_t	pid;

    if (!cmd)
        return ;
    
    current = cmd;
    in_fd = STDIN_FILENO;
    
    while (current)
    {
        out_fd = STDOUT_FILENO;
        
        if (current->pipe_output)
        {
            if (create_pipe(pipefd) == -1)
                return ;
            out_fd = pipefd[1];
        }
        
        if (is_builtin(current->command) && !current->pipe_output)
        {
            current->exit_status = exec_builtin(current->args, (char ***)&envp);
            if (in_fd != STDIN_FILENO)
                close(in_fd);
        }
        else
        {
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return ;
            }
            
            if (pid == 0)
                execute_child(current, in_fd, out_fd, envp);
            else
                current->exit_status = pid;
            
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (out_fd != STDOUT_FILENO)
                close(out_fd);
            
            if (current->pipe_output)
                in_fd = pipefd[0];
        }
        
        current = current->next;
    }
    
    wait_for_children(cmd);
}